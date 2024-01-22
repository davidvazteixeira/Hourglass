# Problems ans Discussions

## The "auto instanciation"

It's handy for begginers but cause some problems

1. It pollutes global namespace.
2. If the user wants a static hourglass controller, the global one still occupies memory
3. It's difficult to remove defines

Maybe a step back and force the user to manually instanciate the controller.
