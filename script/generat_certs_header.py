def make_certs_header(target, source, system_certs_path, builtin_certs):
    src = source
    dst = target
    f = open(src, "rb")
    g = open(dst, "w", encoding="utf-8")
    buf = f.read()
    decomp_size = len(buf)
    import zlib

    buf = zlib.compress(buf)

    g.write("/* THIS FILE IS GENERATED DO NOT EDIT */\n")
    g.write("#ifndef CERTS_COMPRESSED_GEN_H\n")
    g.write("#define CERTS_COMPRESSED_GEN_H\n")

    # System certs path. Editor will use them if defined. (for package maintainers)
    g.write('#define _SYSTEM_CERTS_PATH "%s"\n' % str(system_certs_path))
    if builtin_certs:
        # Defined here and not in env so changing it does not trigger a full rebuild.
        g.write("#define BUILTIN_CERTS_ENABLED\n")
        g.write("static const int _certs_compressed_size = " + str(len(buf)) + ";\n")
        g.write("static const int _certs_uncompressed_size = " + str(decomp_size) + ";\n")
        g.write("static const unsigned char _certs_compressed[] = {\n")
        for i in range(len(buf)):
            g.write("\t" + str(buf[i]) + ",\n")
        g.write("};\n")
    g.write("#endif // CERTS_COMPRESSED_GEN_H")

    g.close()
    f.close()

import sys

if __name__ == "__main__":
    if len(sys.argv) < 5:
        print("usage : " + sys.argv[0] + " <destination> <source> <system_certs_path> <builtin_certs>")
        exit()
    make_certs_header(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4] == "ON")