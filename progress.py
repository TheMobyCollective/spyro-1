import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.ticker as ticker
from git import Repo
import pandas as pd
import datetime
import os
import re


def parse_map_file(map_path):
    """
    Parse the map file to extract function byte sizes for historical tracking.
    Uses symbol addresses to calculate function sizes.
    """
    func_sizes = {}       # function_name -> size in bytes
    addr_to_size = {}     # address -> size in bytes
    addr_to_funcs = {}    # address -> list of function names

    with open(map_path, 'r') as f:
        content = f.read()

    # Parse symbol entries for function sizes
    # Format:   0xADDRESS  symbol_name
    symbol_pattern = re.compile(
        r'^\s+(0x[0-9a-fA-F]+)\s+(\w+)\s*$',
        re.MULTILINE
    )

    symbols = []
    for match in symbol_pattern.finditer(content):
        addr = int(match.group(1), 16)
        name = match.group(2)
        # Filter to main code area and skip internal/data symbols
        if 0x80010000 <= addr < 0x80060000:
            if not name.startswith('__') and not name.startswith('D_'):
                symbols.append((addr, name))
                if addr not in addr_to_funcs:
                    addr_to_funcs[addr] = []
                addr_to_funcs[addr].append(name)

    # Sort by address and deduplicate
    symbols.sort(key=lambda x: x[0])
    seen_addrs = set()
    unique_symbols = []
    for addr, name in symbols:
        if addr not in seen_addrs:
            seen_addrs.add(addr)
            unique_symbols.append((addr, name))

    # Calculate function sizes from address gaps
    for i in range(len(unique_symbols) - 1):
        addr, name = unique_symbols[i]
        next_addr = unique_symbols[i + 1][0]
        size = next_addr - addr

        # Store size by address and all names at that address
        addr_to_size[addr] = size
        for func_name in addr_to_funcs.get(addr, [name]):
            func_sizes[func_name] = size

    return func_sizes, addr_to_size


def get_func_size(func_name, func_sizes, addr_to_size):
    """Get byte size for a function, trying name first, then address extraction."""
    if func_name in func_sizes:
        return func_sizes[func_name]

    # Try to extract address from func_XXXXXXXX pattern
    match = re.match(r'func_([0-9a-fA-F]{8})', func_name)
    if match:
        addr = int(match.group(1), 16)
        if addr in addr_to_size:
            return addr_to_size[addr]

    return 0


def extract_function_names(content):
    """Extract function names and their checked status from progress.md."""
    checked_funcs = []
    unchecked_funcs = []

    for line in content.split('\n'):
        match_checked = re.match(r'- \[x\] (\w+)', line)
        match_unchecked = re.match(r'- \[ \] (\w+)', line)

        if match_checked:
            checked_funcs.append(match_checked.group(1))
        elif match_unchecked:
            unchecked_funcs.append(match_unchecked.group(1))

    return checked_funcs, unchecked_funcs


# Get the script directory
script_dir = os.path.dirname(os.path.realpath(__file__))

# Load data from the map file
map_path = os.path.join(script_dir, 'build', 'psx.map')
if os.path.exists(map_path):
    func_sizes, addr_to_size = parse_map_file(map_path)
else:
    print(f"Warning: Map file not found at {map_path}")
    func_sizes, addr_to_size = {}, {}

# Read git history
repo = Repo(script_dir)
commits = list(repo.iter_commits(paths='progress.md'))

# Process each commit
progress = []
for commit in commits:
    date = commit.committed_datetime
    date = datetime.datetime(date.year, date.month, date.day, 0, 0, 0, tzinfo=datetime.timezone.utc)

    content = commit.tree / 'progress.md'
    content = content.data_stream.read().decode('utf-8')

    checked_funcs, unchecked_funcs = extract_function_names(content)

    # Calculate bytes for matched (C) and non-matching (ASM) functions
    matched_bytes = sum(get_func_size(f, func_sizes, addr_to_size) for f in checked_funcs)
    unmatched_bytes = sum(get_func_size(f, func_sizes, addr_to_size) for f in unchecked_funcs)

    progress.append((
        date,
        len(checked_funcs),
        len(unchecked_funcs),
        matched_bytes,
        unmatched_bytes
    ))

progress = sorted(progress, key=lambda x: x[0])
date_range = pd.date_range(start=progress[0][0], end=progress[-1][0], freq='h')

# Interpolate progress for smooth chart
new_progress = []
for date in date_range:
    funcs_matched = 0
    funcs_unmatched = 0
    bytes_matched = 0
    bytes_unmatched = 0

    for d, fm, fu, bm, bu in progress:
        if d.date() <= date.date():
            funcs_matched = fm
            funcs_unmatched = fu
            bytes_matched = bm
            bytes_unmatched = bu

    total_funcs = funcs_matched + funcs_unmatched
    total_bytes = bytes_matched + bytes_unmatched

    func_pct = (funcs_matched * 100) / total_funcs if total_funcs > 0 else 0
    bytes_pct = (bytes_matched * 100) / total_bytes if total_bytes > 0 else 0

    new_progress.append((date, func_pct, bytes_pct))

progress_df = pd.DataFrame(new_progress, columns=['date', 'functions', 'bytes'])

# Create the chart
fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(progress_df['date'], progress_df['functions'], label='Functions', color='blue', linewidth=2)
ax.plot(progress_df['date'], progress_df['bytes'], label='Bytes', color='red', linewidth=2)

ax.xaxis.set_major_locator(mdates.MonthLocator())
ax.xaxis.set_major_formatter(mdates.DateFormatter('%b %Y'))
ax.xaxis.set_minor_locator(mdates.WeekdayLocator())
ax.set_ylim(0, 100)
ax.yaxis.set_major_formatter(ticker.PercentFormatter())
ax.legend(loc='upper left')
ax.grid(True, alpha=0.3)
ax.set_xlabel('Date')
ax.set_ylabel('Decompilation Progress')

# Get final statistics
final_func_pct = progress_df['functions'].iloc[-1]
final_bytes_pct = progress_df['bytes'].iloc[-1]

final_funcs_matched = progress[-1][1]
final_funcs_total = progress[-1][1] + progress[-1][2]

final_bytes_matched = progress[-1][3]
final_bytes_total = progress[-1][3] + progress[-1][4]

plt.title(
    f'Main Executable Decompilation Progress\n'
    f'Functions: {final_func_pct:.1f}% ({final_funcs_matched}/{final_funcs_total}) | '
    f'Bytes: {final_bytes_pct:.1f}% ({final_bytes_matched:,}/{final_bytes_total:,})'
)
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('.github/assets/progress.png', dpi=150)

# Print summary
print(f"Functions: {final_func_pct:.2f}% ({final_funcs_matched}/{final_funcs_total})")
print(f"Bytes:     {final_bytes_pct:.2f}% ({final_bytes_matched:,}/{final_bytes_total:,})")
