def apply(config, args):
    config["baseimg"] = "build/SCUS_942.28"
    config["myimg"] = "build/PSX.EXE"
    config["mapfile"] = "build/psx.map"
    config["source_directories"] = ["src"]
    config["arch"] = "mipsel"
    config["show_line_numbers_default"] = True