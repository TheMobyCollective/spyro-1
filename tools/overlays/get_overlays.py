# prints the overlay targets for make
from get_overlay_objects import get_overlays

print(" ".join(name for _, name, _, _ in get_overlays()))
