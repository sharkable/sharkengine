var activeDocument = app.activeDocument;
var outputFolder = activeDocument.path + "/output"
var layerVisibleMap = new Array();

var layerIndexes = getLayerSetsIndex();

for (var i = 0; i < layerIndexes.length; i++) {
  var index = layerIndexes[i];
  layerVisibleMap[index] = getLayerVisibilityByIndex(index);
  makeActiveByIndex(index, false);
  activeDocument.activeLayer.visible = false;
}

for (var i = 0; i < layerIndexes.length; i++) {
  makeActiveByIndex(layerIndexes[i], false);
  if (activeDocument.activeLayer.name[0] == "_") {
    createResourceFromLayerSet(activeDocument.activeLayer);
  }
}

for (var i = 0; i < layerIndexes.length; i++) {
  var index = layerIndexes[i];
  makeActiveByIndex(index, false);
  activeDocument.activeLayer.visible = layerVisibleMap[index];
}

function getLayerSetsIndex() {  
   function getNumberLayers() { 
     var ref = new ActionReference(); 
     ref.putProperty(charIDToTypeID("Prpr"), charIDToTypeID("NmbL")); 
     ref.putEnumerated(charIDToTypeID("Dcmn"), charIDToTypeID("Ordn"), charIDToTypeID("Trgt")); 
     return executeActionGet(ref).getInteger(charIDToTypeID("NmbL")); 
   } 

   function hasBackground() {
     var ref = new ActionReference(); 
     ref.putProperty( charIDToTypeID("Prpr"), charIDToTypeID("Bckg")); 
     // bottom Layer/background 
     ref.putEnumerated(charIDToTypeID("Lyr "), charIDToTypeID("Ordn"), charIDToTypeID("Back")); 
     var desc = executeActionGet(ref);
     var res = desc.getBoolean(charIDToTypeID("Bckg"));
     return res   
    };

   function getLayerType(idx,prop) {        
       var ref = new ActionReference(); 
       ref.putIndex(charIDToTypeID("Lyr "), idx);
       var desc = executeActionGet(ref);
       var type = desc.getEnumerationValue(prop);
       var res = typeIDToStringID(type); 
       return res   
    };

   var cnt = getNumberLayers() + 1; 
   var res = new Array(); 

   if (hasBackground()) { 
     var i = 0; 
   } else{ 
     var i = 1; 
   };

   var prop = stringIDToTypeID("layerSection")  
   for(i; i < cnt; i++){ 
      var temp = getLayerType(i, prop); 
      if (temp == "layerSectionStart") res.push(i); 
   }; 
   return res; 
};

function getLayerVisibilityByIndex(idx) {
  var ref = new ActionReference();
  ref.putProperty(charIDToTypeID("Prpr"), charIDToTypeID("Vsbl"));
  ref.putIndex(charIDToTypeID("Lyr " ), idx);
  return executeActionGet(ref).getBoolean(charIDToTypeID("Vsbl"));;
};

function makeActiveByIndex(idx, visible) {
  var desc = new ActionDescriptor();
  var ref = new ActionReference();
  ref.putIndex(charIDToTypeID("Lyr "), idx);
  desc.putReference(charIDToTypeID("null"), ref);
  desc.putBoolean(charIDToTypeID("MkVs"), visible);
  executeAction(charIDToTypeID("slct"), desc, DialogModes.NO);
};

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

function recursiveSetLayerSetVisible(layer, visible) {
  layer.visible = visible;
  var layerSets = layer.layerSets;
  if (layerSets) {
    for (var i = 0; i < layerSets.length; i++) {
     recursiveSetLayerSetVisible(layerSets[i], visible);
    }
  }
}

function setParentsVisible(layerSet, visible) {
  var parent = layerSet.parent; 
  while (parent != activeDocument) {
    parent.visible = visible;	
    parent = parent.parent;
  }  
}

function createResourceFromLayerSet(layerSet) {
  recursiveSetLayerSetVisible(layerSet, true);
  setParentsVisible(layerSet, true);

  activeDocument.selection.selectAll();
  activeDocument.selection.copy(true);
 
  recursiveSetLayerSetVisible(layerSet, false);
  setParentsVisible(layerSet, false);

  var documentName = layerSet.name.substring(1);
  var document = app.documents.add(activeDocument.width, activeDocument.height, 72, documentName,
	                               NewDocumentMode.RGB, DocumentFill.TRANSPARENT);
  pasteInPlace();

  var oldWidth = document.width;
  var oldHeight = document.height;
  document.trim(TrimType.TRANSPARENT, true, true, false, false);
  var x = oldWidth - document.width;
  var y = oldHeight - document.height;
  document.trim(TrimType.TRANSPARENT, false, false, true, true);
  alert(documentName + ' position ' + x + "," + y);

  var pngSaveOptions = new PNGSaveOptions();
  pngSaveOptions.interlaced = false;
  document.saveAs(new File(outputFolder + "/" + documentName), pngSaveOptions, true);
  document.close(SaveOptions.DONOTSAVECHANGES);
}

