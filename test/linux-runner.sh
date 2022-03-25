#!/bin/sh

icewm&
sleep 2

QT_QPA_PLUGIN=minimal exec ninja check
