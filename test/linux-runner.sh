#!/bin/sh

icewm&
sleep 2

exec ninja check
