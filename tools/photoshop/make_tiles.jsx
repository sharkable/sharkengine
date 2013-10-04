var tileSize = 256;

var activeDocument = app.activeDocument;
var outputFolder = activeDocument.path + "/textures";

var response = prompt("It this for Retina Display? iPhone?", 'nn');
var isRetina = response[0] != 'n' && response[0] != 'N';
var isPhone = response[1] != 'n' && response[1] != 'N';

for (i = 0; i < activeDocument.width / tileSize; i++) {
  for (j = 0; j < activeDocument.height / tileSize; j++) {
    createTile(i, j);
  }
}

function createTile(x, y) {
  var documentName = "tile_" + x + "_" + y;
  if (isPhone) {
    documentName += "_iphone";
  }
  if (isRetina) {
    documentName += "@2x";
  }
  var region = Array(Array(x * tileSize, y * tileSize),
                     Array((x + 1) * tileSize, y * tileSize),
                     Array((x + 1) * tileSize, (y + 1) * tileSize),
                     Array(x * tileSize, (y + 1) * tileSize));
  activeDocument.selection.select(region);
  activeDocument.selection.copy(true);
   
  var document = app.documents.add(256, 256, 72, documentName, NewDocumentMode.RGB,
                                   DocumentFill.TRANSPARENT);
  document.paste();
  
  var pngSaveOptions = new PNGSaveOptions();
  pngSaveOptions.interlaced = false;
  document.saveAs(new File(outputFolder + "/" + documentName), pngSaveOptions, true);
  
  document.close(SaveOptions.DONOTSAVECHANGES);
}
