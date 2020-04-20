SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "CLOSED"

SRC_URI= "file://*"

S = "${WORKDIR}"


do_compile() {
	make
}

do_install() {
	install -d ${D}/${bindir}
        install -m 755 detective ${D}/${bindir}

}


FILE_${PN} += "${bindir}/detective"

INSANE_SKIP_${PN} = "ldflags"

INSANE_SKIP_${PN}-dev = "ldflags"
