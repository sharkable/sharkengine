var activeDocument = app.activeDocument;
var activeLayer = activeDocument.activeLayer;
var textureOutputFolder = activeDocument.path + "/textures";

var response = prompt("It this for Retina Display? iPhone?", 'nn');
var isRetina = response[0] != 'n' && response[0] != 'N';
var isPhone = response[1] != 'n' && response[1] != 'N';

var characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.!?,:;%\"";

for (var i = 0; i < characters.length; i++) {
  createLetter(characters.charAt(i))
}

function pasteInPlace() {
  var idpast = charIDToTypeID("past");
  var desc557 = new ActionDescriptor();
  var idinPlace = stringIDToTypeID("inPlace");
  desc557.putBoolean(idinPlace, true);
  var idAntA = charIDToTypeID("AntA");
  var idAnnt = charIDToTypeID("Annt");
  var idAnno = charIDToTypeID("Anno");
  desc557.putEnumerated(idAntA, idAnnt, idAnno);
  executeAction(idpast, desc557, DialogModes.NO);
}

function createLetter(letter) {
  var file_extention;
  if ("ABCDEFGHIJKLMNOPQRSTUVWXYZ".indexOf(letter) != -1) {
    file_extention = letter + "_big";
  } else if (letter == ".") {
    file_extention = "dot";
  } else if (letter == "!") {
    file_extention = "exclamation";
  } else if (letter == "?") {
    file_extention = "question";
  } else if (letter == ",") {
    file_extention = "comma";
  } else if (letter == ":") {
    file_extention = "colon";
  } else if (letter == ";") {
    file_extention = "semicolon";
  } else if (letter == "%") {
    file_extention = "percent";
  } else if (letter == "\"") {
      file_extention = "quote";
  } else {
    file_extention = letter;    
  }

  var documentName = activeLayer.name + "_" + file_extention;
  if (isPhone) {
    documentName += "_iphone";
  }
  if (isRetina) {
    documentName += "@2x";
  }

  activeLayer.textItem.contents = letter;

  activeDocument.selection.selectAll();
  activeDocument.selection.copy(true);
 
  var document = app.documents.add(activeDocument.width, activeDocument.height, 72, documentName,
                                   NewDocumentMode.RGB, DocumentFill.TRANSPARENT);
  pasteInPlace();

  document.trim(TrimType.TRANSPARENT, false, true, false, true);

  var pngSaveOptions = new PNGSaveOptions();
  pngSaveOptions.interlaced = false;
  document.saveAs(new File(textureOutputFolder + "/" + documentName), pngSaveOptions, true);

  document.close(SaveOptions.DONOTSAVECHANGES);
}
