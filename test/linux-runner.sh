#!/bin/sh

icewm&
sleep 2

XDISPLAY=":1"
if [[ -n ${XDISPLAY-} ]]; then
  if [[ "$OSTYPE" != "darwin"* ]]; then
    # 'coproc' so that SIGINT will still work (https://unix.stackexchange.com/a/478697/11592)
    coproc Xvfb ${XDISPLAY} -screen 0 1024x768x16
    VIRT_FB_PID=$!
    sleep 4 # time to (probabilistically) ensure that Xvfb has started
  fi
fi

exec ninja check
