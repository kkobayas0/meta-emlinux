DISTRO_NAME = "EMLinux"
DISTRO_VERSION = "2.7"
DISTRO_CODENAME = "buster"
SDK_VENDOR = "-emlinuxsdk"
SDK_VERSION := "${@'${DISTRO_VERSION}'.replace('snapshot-${DATE}','snapshot')}"

MAINTAINER = "Cybertrust Japan"

TARGET_VENDOR = "-emlinux"

LOCALCONF_VERSION = "1"

DISTRO_VERSION[vardepsexclude] = "DATE"
SDK_VERSION[vardepsexclude] = "DATE"

# Override these in poky based distros
EMLINUX_DEFAULT_DISTRO_FEATURES = "largefile opengl ptest multiarch wayland vulkan systemd"
EMLINUX_DEFAULT_EXTRA_RDEPENDS = "packagegroup-core-boot"

DISTRO_FEATURES ?= "${DISTRO_FEATURES_DEFAULT} ${DISTRO_FEATURES_LIBC} ${EMLINUX_DEFAULT_DISTRO_FEATURES}"

SDK_NAME = "${DISTRO}-${TCLIBC}-${SDK_ARCH}-${IMAGE_BASENAME}-${TUNE_PKGARCH}"
SDKPATH = "/opt/${DISTRO}/${SDK_VERSION}"

DISTRO_EXTRA_RDEPENDS += " ${EMLINUX_DEFAULT_EXTRA_RDEPENDS}"

# Common values for git access of Linux Kernel
LINUX_GIT_URI ?= "git://git.kernel.org/pub/scm/linux/kernel/git/cip"
LINUX_GIT_PROTOCOL ?= "https"
LINUX_GIT_PREFIX ?= ""
LINUX_GIT_REPO ?= "linux-cip.git"

# use toolchain mode for Debian instead of the default
TCMODE ?= "emlinux"

# Add an eventhandler that generates DEBIAN_SRC_URI information
# from Debian apt repository.
INHERIT += "debian-source"

QEMU_TARGETS ?= "arm aarch64 i386 x86_64"

PREMIRRORS ??= "\
bzr://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n \
cvs://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n \
git://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n \
gitsm://.*/.* http://downloads.yoctoproject.org/mirror/sources/ \n \
hg://.*/.*    http://downloads.yoctoproject.org/mirror/sources/ \n \
osc://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n \
p4://.*/.*    http://downloads.yoctoproject.org/mirror/sources/ \n \
svn://.*/.*   http://downloads.yoctoproject.org/mirror/sources/ \n"

MIRRORS =+ "\
ftp://.*/.*      http://downloads.yoctoproject.org/mirror/sources/ \n \
http://.*/.*     http://downloads.yoctoproject.org/mirror/sources/ \n \
https://.*/.*    http://downloads.yoctoproject.org/mirror/sources/ \n"

SANITY_TESTED_DISTROS ?= " \
            ubuntu-18.04 \n \
            ubuntu-20.04 \n \
            "

#
# OELAYOUT_ABI allows us to notify users when the format of TMPDIR changes in
# an incompatible way. Such changes should usually be detailed in the commit
# that breaks the format and have been previously discussed on the mailing list
# with general agreement from the core team.
#
OELAYOUT_ABI = "12"

# QA check settings - a little stricter than the OE-Core defaults
WARN_TO_ERROR_QA = "already-stripped compile-host-path install-host-path \
                    installed-vs-shipped ldflags pn-overrides rpaths staticdev \
                    unknown-configure-option useless-rpaths"
WARN_QA_remove = "${WARN_TO_ERROR_QA}"
ERROR_QA_append = " ${WARN_TO_ERROR_QA}"

BB_HASHBASE_WHITELIST_append = " DEBIAN_UNPACK_DIR"

require conf/distro/include/yocto-uninative.inc
require conf/distro/include/no-static-libs.inc
INHERIT += "uninative"
