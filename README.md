![Logo](https://s3.amazonaws.com/com.twilio.prod.twilio-docs/images/hackpack_in_dock.jpg)

# Hackpack v3

Hackpack v3 is a limited-edition hardware badge fabricated for [SIGNAL 2017](https://www.twilio.com/signal), _The Developer Conference_ by [Twilio](https://twilio.com).

Onboard is a Particle Electron 3G from [Particle](https://www.particle.io/), 16 Neopixel RGB LEDs, and a 2000 mAh Lithium Ion Battery.

## Getting Started

We've written up an extensive guide for getting your Hackpack connected with your phone number and the consoles on the dedicated [Hackpack site](https://hackpack.cc/).  Before you wade into the code, make sure you've followed all of the steps to claim your device, and have successfully connected to one of the two podium consoles.

## Prerequisites and Installation

The firmware on the Hackpack is designed for use with [Particle's Web IDE](https://build.particle.io/).  While at SIGNAL 2017 (and after your device is claimed in the Web IDE), you can burn the firmware in this repository to return your Hackpack to stock condition.  

With a lifeline like that, feel free to swing for the fences with your hacks!

## Getting Started Hacking the Hackpack

Want some examples of what you can do with the badge?

Here are some hacks to get you started:

* [Font and String Generator](https://gist.github.com/pkamp3/d114d89d45939ab20fb83706868f37fb)
* [Animated GIF and Movie Converter](https://gist.github.com/pkamp3/5ea656b8b67c9d8f19daa72ff26bcf89)
* [Rainbow Animation and a Golden State Warriors Logo](https://gist.github.com/jarodreyes/d9905fda321a9e69de87271015e1bc1a)
* [Hackpack and PagerDuty](https://github.com/flyandi/hackpackv3-pagerduty)

For these hacks, you will just overwrite the `uint32_t custom_animation_lut[][16]` array in the .ino file.

## More Advanced Hacking

* [Custom Firmware Fork to Add Morse Code](https://github.com/rbeiter/hackpack-v3)

For this hack, you'll want to switch to @rbeiter 's repo and burn your Hackpack with his fork.  You can also add the other hacks as well!

### Built something great with your Hackpack?

Show us the creative hacks you build on top of our firmware.  We want to let your work shine as brightly as the pixels on the big screen and your Hackpack - we'll add you to this list during SIGNAL!

## Meta & Licensing

* MIT License
* Lovingly crafted by your friends at [Twilio](https://twilio.com), [Particle](http://particle.io/), and [Deeplocal](http://deeplocal.com/)
