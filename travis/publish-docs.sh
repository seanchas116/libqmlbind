#!/usr/bin/env bash

# GH_TOKEN is a github personal OAUTH tokens, create it here:
# https://github.com/settings/tokens/new (only needs “repo“ access.)
# Then, add them as hidden environment variable in the Travis project settings.
GH_REPO="seanchas116/libqmlbind"
WEBROOT="doc/html"

skip() {
	echo "SKIPPING: $@" 1>&2
	echo "Exiting..."
	exit 0
}

install-deps() {
  # install doxygen 1.8.11 from binary, because older versions throw errors on markdown code with images inside links
  # (like the build status in the readme) and it's the only way to get a newer doxygen in Ubuntu 14.04
  # doxygen binary install based on https://github.com/gadomski/fgt/blob/master/scripts/gh-pages.sh
  DOXYGEN_VER=doxygen-1.8.11
  DOXYGEN_TAR=${DOXYGEN_VER}.linux.bin.tar.gz
  DOXYGEN_URL="http://ftp.stack.nl/pub/users/dimitri/${DOXYGEN_TAR}"
  sudo pip install ghp-import
  wget -O - "${DOXYGEN_URL}" | tar xz -C ${TMPDIR-/tmp} ${DOXYGEN_VER}/bin/doxygen
  export PATH="${TMPDIR-/tmp}/${DOXYGEN_VER}/bin:$PATH"
}

if [ "${TRAVIS}" = "true" ]; then
	[ "${TRAVIS_OS_NAME}" = "osx" ] || skip "Not building docs on OSX"
	[ "${TRAVIS_PULL_REQUEST}" = "false" ] || skip "Not building docs for pull requests"
	[ "${TRAVIS_BRANCH}" = "master" ] || skip "Only building docs for master branch"
	[ "${TRAVIS_JOB_NUMBER}" = "${TRAVIS_BUILD_NUMBER}.1" ] || skip "Only build docs once"

  install-deps
  doxygen

	git config user.name "Travis CI"
	git config push.default simple
	ghp-import -n -m "Updated documentation from ${TRAVIS_COMMIT}" ${WEBROOT}
	git push -fq "https://${GH_TOKEN}@github.com/${GH_REPO}.git" gh-pages
	echo "documentation was pushed."
fi

# script from: https://github.com/alacarte-maps/alacarte/blob/master/.travis-publish-docs.sh
# based on: https://github.com/gadomski/fgt/blob/master/scripts/gh-pages.sh
# TODO: it would be nice to be able to publish the docs of multiple branches in subfolders, e.g. master and stable
