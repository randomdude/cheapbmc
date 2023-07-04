from PySide2 import QtCore

import FreeCAD
import FreeCADGui

import BOPTools.SplitFeatures
import Part

from lasercut.tabproperties import TabProperties

from exportutils import *

import math
import os

def main():
	doc = FreeCAD.ActiveDocument
	if 'exported_' not in doc.Name:
		raise Exception("Run build scripts on a copy of the input, not the original")

	doc.recompute()

	builder = tabbedObjectBuilder(["front", "back", "bottomWithHoles", "sidesWithHoles"], cutterMaterial.bamboo(3))

	# Now we must add any faces which we want to process. 

	# We want the downward faces on the case sides. Note the large tabs on the sides - this is to try to put as much support material around
	# the holes as we can.
	builder.createTabsByFaceNormal("front", FreeCAD.Vector( 0, 0, -1), tabWidth = 5, tabNumber = 5)
	builder.createTabsByFaceNormal("back", FreeCAD.Vector( 0, 0, -1), tabWidth = 5, tabNumber = 5)
	builder.createTabsByFaceNormal("sidesWithHoles", FreeCAD.Vector( 0, 0, -1), tabWidth = 47, tabNumber = 2)
	if len(builder.getFaces()) != 4:
		raise Exception("Did not find Z-pointing face on case bottom to add tabs to")

	# Now sideways (x-ward) facing faces on the case bottom and top.
	for objName in ["front", "back"]:
		builder.createTabsByFaceNormal(objName, FreeCAD.Vector( +1,  0,  0), tabWidth = 5)
		builder.createTabsByFaceNormal(objName, FreeCAD.Vector( -1,  0,  0), tabWidth = 5)

	if len(builder.getFaces()) != 8:
		raise Exception("Did not find x-pointing faces on case sides to add tabs to")

	# Make the tabs..
	tabbedObjects = builder.execute()

	# Align our tabbed object to the z plane
	exporter = exportutils(tabbedObjects, builder.material)
	exporter.rotateAndPositionAllObjectsOnZ()

	# Rotate the two supports so the result causes less wastage
	for obj in tabbedObjects:
		if obj.Shape.BoundBox.YLength < 40:
			obj.Placement.Rotation = obj.Placement.Rotation.multiply(FreeCAD.Rotation(FreeCAD.Base.Vector(0,1,0),90))

	# Now we can place our objects one after another, in a neat row.
	exporter.placeInRow(tabbedObjects, startPosX = 10, startPosY = 10)

	# Finally, we can use the CAM code to generate some gcode and export the results.
	exporter.execute()
	exporter.saveGCode()
	exporter.saveScreenshotOfPath()

try:
	main()
	FreeCADGui.getMainWindow().deleteLater()
except Exception as e:
	FreeCAD.Console.PrintError(str(e) + "\n")
	FreeCADGui.getMainWindow().deleteLater()
