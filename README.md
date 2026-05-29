>[!WARNING]
There are some issues with the module that needs to be sorted out before it can be added to SyatiManager.

This works with Super Mario Galaxy 2 (SB4E01). Not sure about other regions. Nintendo Switch port is not supported nor planned.

### Setup
You MUST add the following entries to your `ProductMapObjDataTable.bcsv`:

*QuestionBoxPlanetA*, *QuestionBoxGalleryObj* (ModelName, ClassName)<br>
*QuestionBoxPlanetB*, *QuestionBoxGalleryObj* (ModelName, ClassName)<br>
*QuestionBoxPlanetC*, *QuestionBoxGalleryObj* (ModelName, ClassName)<br>
*QuestionBoxPlanetD*, *QuestionBoxGalleryObj* (ModelName, ClassName)<br>
*QuestionBoxMoveStepA*, *QuestionBoxGalleryObj* (ModelName, ClassName)<br>
*QuestionBoxMoveStepB*, *QuestionBoxGalleryObj* (ModelName, ClassName)<br>
*QuestionBoxMoveStepC*, *QuestionBoxGalleryObj* (ModelName, ClassName)<br>

### Object-Specific Arguments (MapPart: QuestionBoxMoveStepA)
*Note that the current list of arguments may be subject to any corrections, if needed*
> See RotateMoveObj for configuring the rotation settings of this object.

### Object-Specific Arguments (MapPart: QuestionBoxMoveStepB, QuestionBoxMoveStepC)
*Note that the current list of arguments may be subject to any corrections, if needed*
> See RailMoveObj for configuring the path settings of this object.

### Global (Module) Object Arguments
*Note that the current list of arguments may be subject to any corrections, if needed*
> **SW_A**<br>
Triggers the object's On state animation and effects.<br><br>
**SW_B**<br>
Triggers the object's Off state animation and effects.<br><br>

If you're still not understanding how to set this object up correctly, and you have a copy of Super Mario Galaxy (2007), look in the `QuestionBoxZone` in the level editor.