import yaml
import sys

with open("overlays/mobys.yaml", "r") as f:
    overlay_name = sys.argv[1]
    particles = yaml.safe_load(f)

    particle_list = []
    for particle_class, data in particles.items():
        if data["overlays"] is not None and (data["overlays"] == "ALL" or overlay_name in data["overlays"]):
            particle_list.append(str(particle_class))

    print(",".join(particle_list))
    