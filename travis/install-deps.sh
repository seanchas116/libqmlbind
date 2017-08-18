#!/usr/bin/env bash

if [[ "$TRAVIS_OS_NAME" == "osx"  ]]; then
    brew install qt5
    brew link qt5 --force
else
    sudo apt-get update -qq
    sudo apt-get install -qq qtbase5-dev libqt5gui5 libqt5quick5 libqt5qml5 qtdeclarative5-dev qtdeclarative5-qtquick2-plugin
fi
