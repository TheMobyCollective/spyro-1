# From overlays/overlays.yaml, print which object files need to be compiled for all overlays
import yaml

def get_overlays():
    with open("overlays/overlays.yaml", "r") as f:
        return [(overlay["psyq_overlay_index"], overlay["name"], overlay["files"] or [], overlay.get("padding_garbage", [])) for overlay in yaml.safe_load(f)]

def overlay_obj_name(overlay_name, file):
    return "build/src/overlays/" + overlay_name + "/" + file.replace(".c", ".o")

if __name__ == "__main__":
    print(" ".join(overlay_obj_name(name, file) for _, name, files, _ in get_overlays() for file in files))
