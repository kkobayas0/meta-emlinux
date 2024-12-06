# This recipe is imported from meta-openembedded.
# base recipe meta-filesystems/recipes-utils/exfatprogs/exfatprogs_1.2.5.bb
# base branch master
# base commit a9cb23d9414d841748738235230c68823e61ed98

SUMMARY = "exFAT filesystem userspace utilities"
DESCRIPTION = "\
As new exfat filesystem is merged into linux-5.7 kernel, exfatprogs is \
created as an official userspace utilities that contain all of the standard \
utilities for creating and fixing and debugging exfat filesystem in linux \
system. The goal of exfatprogs is to provide high performance and quality \
at the level of exfat utilities in windows. And this software is licensed \
under the GNU General Public License Version 2."
HOMEPAGE = "https://github.com/${BPN}/${BPN}"
SECTION = "universe/otherosfs"
LICENSE = "GPL-2.0"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

SRC_URI = "https://github.com/${BPN}/${BPN}/releases/download/${PV}/${BP}.tar.xz"
SRC_URI[sha256sum] = "f27160dcc1ddd17c96cd41a6ceef7037adc2796ab5c5633d3d85cf532c3ee2f0"

UPSTREAM_CHECK_URI = "https://github.com/${BPN}/${BPN}/releases"
UPSTREAM_CHECK_REGEX = "${BPN}-(?P<pver>\d+(\.\d+)+)"

inherit autotools ptest

RPROVIDES_${PN} = "exfat-utils"
RCONFLICTS_${PN} = "exfat-utils"
RREPLACES_${PN} = "exfat-utils"

SRC_URI += "\
  file://run-ptest \
  file://test_file_creation.sh \
"

RDEPENDS_${PN}-ptest = "tar xz"
do_install_ptest() {
  install -d ${D}/${PTEST_PATH}/tests
  install -d ${D}/${PTEST_PATH}/test_file_creation

  install -m0755 ${WORKDIR}/run-ptest ${D}/${PTEST_PATH}/
  install -m0755 ${WORKDIR}/test_file_creation.sh ${D}/${PTEST_PATH}/test_file_creation/

  cp -r --no-preserve=ownership ${S}/tests/* ${D}/${PTEST_PATH}/tests/
}
