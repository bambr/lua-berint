rockspec_format = "1.0"
package = "berint"
version = "1.0-1"
source = {
    url = "git://github.com/bambr/lua-berint",
    tag = "v1.0"
}
description = {
    summary = "Encoder and decoder for BER compressed integers",
    homepage = "https://github.com/bambr/lua-berint",
    license  = 'MIT';
    maintainer = "Sergey Panteleev <bambr@cpan.org>"
}
dependencies = {
    "lua >= 5.1"
}
build = {
    type = 'builtin',
    modules = {
        ['berint'] = {
            sources = {
                "berint.c",
            },
            libraries = {
                "m",
            }
        },
    },
}
