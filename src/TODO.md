The creation of the HourglassController and all the static method turns the static methods inside the Hourglass
useless.

- [X] The Hourglass class must be responsible only for self.
- [ ] All the static methods must be moved to HourglassController
- [ ] All the static initializations must be moved to HourglassController instance initialization
- [ ] In normal use, the user must use just the controller, not the Hourglass
- [ ] The user can rename the default instance with a define:

    #define HOURGLASSES_CONTROLLER_NAME hg

    #ifdef HOURGLASS_CONTROLLER_NAME
      HourglassController HOURGLASS_CONTROLLER_NAME;
    #else
      HourglassController Hourglasses;
    #endif
