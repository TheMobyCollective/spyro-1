# Tool for stripping out cases from switch statements in C code
import re
import sys

TOKEN_RE = re.compile(
    r"""
      \#.*
    | "(?:\\.|[^"\\])*"
    | '(?:\\.|[^'\\])*'
    | \w+
    | \S
    """,
    re.VERBOSE,
)

def tokenize(src):
    return [m for m in TOKEN_RE.finditer(src) if m[0][0] != "#"]

def matching(tokens, i):
    opener, closer = tokens[i][0], {"(": ")", "{": "}"}[tokens[i][0]]
    depth = 0
    for j in range(i, len(tokens)):
        if tokens[j][0] == opener:
            depth += 1
        elif tokens[j][0] == closer:
            depth -= 1
            if depth == 0:
                return j
    raise SyntaxError(f"unclosed {opener}!!")

def find_function_body(tokens):
    decl_start = 0
    i = 0
    while i < len(tokens):
        if tokens[i][0] == "{":
            is_function = tokens[i - 1][0] == ")"
            is_static = "static" in (t[0] for t in tokens[decl_start:i])

            # Static functions don't count, currently
            # not used in practice but I can imagine someone might
            if is_function and not is_static:
                return i
            
            i = matching(tokens, i)
            decl_start = i + 1
        elif tokens[i][0] == ";":
            decl_start = i + 1
        i += 1
    raise SyntaxError("couldn't find any function with a body")

def find_switch_body(tokens, start):
    i = next(i for i in range(start, len(tokens)) if tokens[i][0] == "switch")
    return matching(tokens, i + 1) + 1

def find_labels(tokens, body):
    labels = []
    depth = 0
    for i in range(body, matching(tokens, body)):
        text = tokens[i][0]
        if text == "{":
            depth += 1
        elif text == "}":
            depth -= 1
        elif depth == 1 and text == "case":
            end = next(j for j in range(i, len(tokens)) if tokens[j][0] == ":") + 1
            lo, hi = int(tokens[i + 1][0], 0), int(tokens[end - 2][0], 0)
            labels.append((i, end, range(lo, hi + 1)))
        elif depth == 1 and text == "default":
            labels.append((i, i + 2, ["default"]))
    return labels


def filter_switch(src, keep_cases):
    tokens = tokenize(src)
    body = find_switch_body(tokens, find_function_body(tokens))
    labels = find_labels(tokens, body)
    next_starts = [start for start, _, _ in labels[1:]] + [matching(tokens, body)]

    cuts = []
    code_kept = False
    for (start, end, values), next_start in zip(labels, next_starts):
        # We always keep defaults for moby_spawn.c
        kept = [v for v in values if v in keep_cases or v == "default"]
        if kept:
            code_kept = True
            # Case ranges with missing values get split up
            # in one line because otherwise the line number shifts
            if len(kept) < len(values):
                cuts.append((start, end, " ".join(f"case {v}:" for v in kept)))
        else:
            # Otherwise we start slicing :)
            cuts.append((start, end, ""))
        has_code = end < next_start
        if has_code:
            if not code_kept:
                cuts.append((end, next_start, ""))
            code_kept = False

    # First is where the cut starts, end is where it ends
    # text is new text to insert (for replacing case range labels if needed)
    for first, end, text in reversed(cuts):
        start, stop = tokens[first].start(), tokens[end - 1].end()
        # We insert some newlines to preserve the original line numbers
        # in the hope one day we could still debug this stuff with gdb lmfao
        src = src[:start] + text + "\n" * src.count("\n", start, stop) + src[stop:]
    return src


cases = [int(c, 0) for c in sys.argv[1].split(",") if c]
sys.stdout.write(filter_switch(sys.stdin.read(), cases))