# simple-2d-level-editor
!!!!!! The base-code-rework branch is work in progress. It does not yet have all the features of the main branch. I started it with the idea of reworking my existing code base as I then had a better idea of how things would be coupled. A camera and camera manager classes still need to be implemented in order to rotate the view like in Fez. This is the only feaure from the main branch that has yet to be implemented.


!!!!!! This is very early stages and all is subject to change. !!!!!!


Simple top-down view level editor and which can load the level in a 2D sidescrolling game based on SFML and no engine. Although the character can move in 2D planes the player can change which 2D plane that is giving him the feel of playing in a 3D space. All objects in the game world however are truly 2D. 

To place a red tile click with RMB, green - LMB. To place the character click scroll on mouse. LCtrl + S saves the map. LCtrl + G starts the game and LCtrl + L loads the map. You cannot really play the game yet.

When playing the game you can "rotate" the camera by pressing Q and E to rotate it to the left and right respectively.
