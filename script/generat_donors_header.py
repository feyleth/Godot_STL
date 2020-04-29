import utils
def make_donors_header(target, source):
    sections = [
        "Platinum sponsors",
        "Gold sponsors",
        "Mini sponsors",
        "Gold donors",
        "Silver donors",
        "Bronze donors",
    ]
    sections_id = [
        "DONORS_SPONSOR_PLAT",
        "DONORS_SPONSOR_GOLD",
        "DONORS_SPONSOR_MINI",
        "DONORS_GOLD",
        "DONORS_SILVER",
        "DONORS_BRONZE",
    ]

    src = source
    dst = target
    f = open(src, "r", encoding="utf-8")
    g = open(dst, "w", encoding="utf-8")

    g.write("/* THIS FILE IS GENERATED DO NOT EDIT */\n")
    g.write("#ifndef DONORS_GEN_H\n")
    g.write("#define DONORS_GEN_H\n")

    reading = False

    def close_section():
        g.write("\t0\n")
        g.write("};\n")

    for line in f:
        if reading >= 0:
            if line.startswith("    "):
                g.write('\t"' + utils.escape_string(line.strip()) + '",\n')
                continue
        if line.startswith("## "):
            if reading:
                close_section()
                reading = False
            for section, section_id in zip(sections, sections_id):
                if line.strip().endswith(section):
                    current_section = utils.escape_string(section_id)
                    reading = True
                    g.write("const char *const " + current_section + "[] = {\n")
                    break

    if reading:
        close_section()

    g.write("#endif // DONORS_GEN_H\n")

    g.close()
    f.close()

import sys

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("usage : " + sys.argv[0] + " <destination> <source>")
        exit()
    make_donors_header(sys.argv[1],sys.argv[2])