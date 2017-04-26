// Author:  Ulrich Belitz
// Created on: 2012-12-10

/*
ToDo
- add description at the beginning of the file
- refactoring double code

Done
- possibility to supress table and image captions
- Refactoring Chapter Counters -> Array
- Author und Last Change aus CVS verwenden
- Title über das Inhaltsverzeichnis
- Verlinkung von Kapiteln
- set and link internal hrefs for contents
- automatische Nummerierung der Überschriften
- set tooltip for table data
*/

// global variables
var contents = null;
var bodyChilds = null;
var body = null;
var counter = 0;
var navigationLinkBaseName = "nav";
var imageCounter = 1;
var tableCounter = 1;
var headerCounters = 0;
var headerSeperator = ".";

function checkBrowserName(name){  
  var agent = navigator.userAgent.toLowerCase();
  if (agent.indexOf(name.toLowerCase()) > -1) {
    return true;  
  }
  return false;  
}

function init(doNotCreateCaptionsAndLists, enableFullWidth) {
  if (checkBrowserName('MSIE')){
    // mit IE gibt es leider zu viele Probleme, so dass nichts weiter ausgeführt wird
    return;
  }

  initVariables();
  prettyPrintFooter();
  createContents();
  createTitle();
  initTables();
  if (!doNotCreateCaptionsAndLists) {
    createTableCaptions();
    createImageCaptions();
    createListOfTables();
    createListOfFigures();
  }
  createTableToolTips();
  if (enableFullWidth) {
    body.style.maxWidth = window.innerWidth + "px";
  }
}

function prettyPrintFooter() {
  prettyPrintCVSTagsById("lastChange");
  prettyPrintCVSTagsById("author");
  prettyPrintCVSTagsById("revision");
}

function prettyPrintCVSTagsById (id) {
  var element = window.document.getElementById(id);
  if (element == null) {
    return;
  }
  var lastChangeText = element.textContent;
  if (id == "lastChange") {
    lastChangeText = lastChangeText.replace("$Date: ", "");
  }
  if (id == "author") {
    lastChangeText = lastChangeText.replace("$Author: ", "");
  }
  if (id == "revision") {
    lastChangeText = lastChangeText.replace("$Revision: ", "");
  }
  lastChangeText = lastChangeText.replace(" $", "");
  element.textContent = lastChangeText;
}

function createContents() {
  contents = window.document.createElement("div");
  body.insertBefore(contents, body.firstChild);
  
  if (window.document.getElementsByTagName("h1").length == 0) {
    return;
  }
  
  contents.setAttribute("class", "contents");
  
  var a = window.document.createElement("a");
  a.setAttribute("name", navigationLinkBaseName + counter);
  contents.appendChild(a);
  counter++;

  var contentsHeading = window.document.createElement("div");
  contentsHeading.textContent = "Inhaltsverzeichnis";
  contentsHeading.setAttribute("class", "contentsHeading");
  contents.appendChild(contentsHeading);

  var headerNumber = null;
  for (var i = 0; i < bodyChilds.length; i++) {
    switch(bodyChilds[i].nodeName.toUpperCase()) {
    case "H1":
    case "H2":
    case "H3":
    case "H4":
    case "H5":
    case "H6":
      createNewContentsEntry(bodyChilds[i].nodeName, bodyChilds[i]);
      break;
    }
  }
}

function createTitle() {
  var titles = window.document.getElementsByTagName("title");
  
  if (titles.length == 0) {
    return;
  }
  
  var title = titles[0];
  
  var div = window.document.createElement("div");
  body.insertBefore(div, body.firstChild);
  
  div.setAttribute("class", "title");
  div.textContent = title.textContent;
}

function createNewContentsEntry(tagname, node) {
  // create headerNumber
  var level = parseInt(tagname[1]);
  headerNumber = "";
  headerCounters[level - 1]++;
  for (var i = level; i < headerCounters.length; i++) {
    headerCounters[i] = 0;
  }
  for (var i = 0; i < level; i++) {
    headerNumber += headerCounters[i]
    if (i != level -1) {
      headerNumber += headerSeperator;
    }
  }

  // create navigation element
  var newDiv = window.document.createElement("div");
  var a = window.document.createElement("a");
  newDiv.appendChild(a);
  newDiv.setAttribute("class", "contentsH" + level);
  a.textContent = headerNumber + " " +  node.textContent;
  contents.appendChild(newDiv);
  
  // set headerNumber
  node.textContent = headerNumber + " " + node.textContent;
  
  // set link for internal navigation
  var navigationLink = navigationLinkBaseName + counter;
  a.setAttribute("href", "#" + navigationLink)
  var a2 = window.document.createElement("a");
  a2.setAttribute("name", navigationLink);
  node.insertBefore(a2, node.firstChild);
  
  // find references and link them
  var id = node.getAttribute("id");
  if (id != null) {
    var links = window.document.getElementsByClassName(id);
    for (var i = 0; i < links.length; i++) {
      var link = links[i];
      var nobr = window.document.createElement("nobr");
      var a3 = window.document.createElement("a");
      a3.setAttribute("href", "#" + navigationLink);
      a3.textContent = "Kapitel " + headerNumber;
      link.textContent = "";
      nobr.appendChild(a3);
      link.appendChild(nobr);
    }
  }
  counter++;
}

function initVariables() {
  body = window.document.getElementsByTagName("body")[0];
  bodyChilds = body.childNodes;
  headerCounters = new Array(0, 0, 0, 0, 0, 0);
}

function createTableToolTips() {
  var tables = window.document.getElementsByTagName("table");
  for(var i = 0; i < tables.length; i++) {
    var table = tables[i];
    var tr = table.getElementsByTagName("tr");
    
    var th = tr[0].getElementsByTagName("th");
    
    if (tr.length < 2) {
      return;
    }
    for (var j = 1; j < tr.length; j++) {
      var td = tr[j].getElementsByTagName("td");
      for (var k = 0; k < th.length; k++) {
        td[k].setAttribute("title", th[k].textContent);
      }
    }
    
  }
}

function createImageCaptions() {
  var images = window.document.getElementsByTagName("img");
  for(var i = 0; i < images.length; i++) {
    var img = images[i];
    
    var divImage = window.document.createElement("div");
    divImage.setAttribute("class", "image");
    
    var divImageCaption = window.document.createElement("div");
    divImageCaption.setAttribute("class", "imageCaption");
    
    var divImageCaptionTextContent = "Abbildung " + imageCounter;
    
    var title = img.getAttribute("title");
    if (title != null) {
      if (title.length > 0) {
        divImageCaptionTextContent += ": ";
        divImageCaptionTextContent += title;
      }
    }
    
    divImageCaption.textContent = divImageCaptionTextContent;
    
    img.parentNode.insertBefore(divImage, img);
    divImage.appendChild(img);
    
    divImage.appendChild(divImageCaption);
    
    // links to image
    var id = img.getAttribute("id");    
    if (id != null) {
      var a2 = window.document.createElement("a");
      a2.setAttribute("name", id);
      divImage.insertBefore(a2, divImage.firstChild);
      
      var spans = window.document.getElementsByClassName(id);
      for (var j = 0; j < spans.length; j++) {
        spans[j].textContent = "";
        var a = window.document.createElement("a");
        var nobr = window.document.createElement("nobr");
        a.setAttribute("href", "#" + id);
        a.textContent = "Abbildung " + imageCounter;
        nobr.appendChild(a);
        spans[j].appendChild(nobr);
      }
    }
    
    imageCounter++;
  }
}

function createListOfFigures() {
  // the function createImageCaptions() must be completed before!
  
  var images = window.document.getElementsByTagName("img");
  if (images.length < 1) {
    return;
  }
  
  var listOfFigures = window.document.createElement("div");
  listOfFigures.setAttribute("class", "contents");
  body.insertBefore(listOfFigures, contents.nextSibling);
  
  var contentsHeading = window.document.createElement("div");
  contentsHeading.textContent = "Abbildungsverzeichnis";
  contentsHeading.setAttribute("class", "contentsHeading");
  listOfFigures.appendChild(contentsHeading);
  
  for(var i = 0; i < images.length; i++) {
    var image = images[i];
    
    var id = image.getAttribute("id");
    
    if (id == null) {
      id = (navigationLinkBaseName + counter);
      image.setAttribute("id", id);
      counter++;
    }
    
    var a = window.document.createElement("a");
    a.setAttribute("href", "#" + id);
    a.textContent = image.nextSibling.textContent;
    
    var div = window.document.createElement("div");
    div.appendChild(a);
    
    listOfFigures.appendChild(div);
  }
}

function createTableCaptions() {
  var tables = window.document.getElementsByTagName("table");
  for(var i = 0; i < tables.length; i++) {
    var table = tables[i];
    
    var divTable = window.document.createElement("div");
    divTable.setAttribute("class", "table");
    
    var divTableCaption = window.document.createElement("div");
    divTableCaption.setAttribute("class", "tableCaption");
    var divTableCaptionTextContent = "Tabelle " + tableCounter;
    
    
    var title = table.getAttribute("title");
    if (title == "noCaption") {
      continue;
    }
    if (title != null) {
      if (title.length > 0) {
        divTableCaptionTextContent += ": ";
        divTableCaptionTextContent += title;
      }
    }
    
    divTableCaption.textContent = divTableCaptionTextContent;
    
    table.parentNode.insertBefore(divTable, table);
    divTable.appendChild(table);
    
    divTable.appendChild(divTableCaption);
    
    // links to table
    var id = table.getAttribute("id");
      
    if (id != null) {
      var a2 = window.document.createElement("a");
      a2.setAttribute("name", id);
      divTable.insertBefore(a2, divTable.firstChild);
      
      var spans = window.document.getElementsByClassName(id);
      for (var j = 0; j < spans.length; j++) {
        spans[j].textContent = "";
        var a = window.document.createElement("a");
        var nobr = window.document.createElement("nobr");
        a.setAttribute("href", "#" + id);
        a.textContent = "Tabelle " + tableCounter;
        nobr.appendChild(a);
        spans[j].appendChild(nobr);
      }
    }
    
    tableCounter++;
  }
}

function createListOfTables() {
  // the function createTableCaptions() must be completed before!
  
  var tables = window.document.getElementsByTagName("table");
  if (tables.length < 1) {
    return;
  }
  
  var listOfTables = window.document.createElement("div");
  listOfTables.setAttribute("class", "contents");
  body.insertBefore(listOfTables, contents.nextSibling);
  
  var contentsHeading = window.document.createElement("div");
  contentsHeading.textContent = "Tabellenverzeichnis";
  contentsHeading.setAttribute("class", "contentsHeading");
  listOfTables.appendChild(contentsHeading);
  
  for(var i = 0; i < tables.length; i++) { 
    var table = tables[i];
    
    var title = table.getAttribute("title");
    if (title == "noCaption") {
      continue;
    }
    
    var id = table.getAttribute("id");
    
    if (id == null) {
      id = (navigationLinkBaseName + counter);
      table.setAttribute("id", id);
      counter++;
    }
    
    var a = window.document.createElement("a");
    a.setAttribute("href", "#" + id);
    a.textContent = table.nextSibling.textContent;
    
    var div = window.document.createElement("div");
    div.appendChild(a);
    
    listOfTables.appendChild(div);
  }
}

function initTables() {
  var tables = window.document.getElementsByTagName("table");
  for (var i = 0; i < tables.length; i++) {
    tables[i].setAttribute("ondblclick", "tableToCSV(this)");
  }
}

function tableToCSV(table) {
  var textareas = table.parentNode.getElementsByTagName("textarea");
  var textarea;
  if (textareas.length == 0) {
    textarea = window.document.createElement("textarea");
    table.parentNode.insertBefore(textarea, table);
  }
  else {
    textarea = textareas[0];
  }
  textarea.setAttribute("cols", 150);
  textarea.setAttribute("onclick", "this.select()");
  var trs = table.getElementsByTagName("tr");
  var resultString = "";
  for (var i = 0; i < trs.length; i++) {
    var ths = trs[i].getElementsByTagName("th");
    for (var j = 0; j < ths.length; j++) {
      resultString += ths[j].textContent;
      if (j != ths.length - 1) {
        resultString += ";";
      }
    }
    var tds = trs[i].getElementsByTagName("td");
    for (var j = 0; j < tds.length; j++) {
      resultString += tds[j].textContent;
      if (j != tds.length - 1) {
        resultString += ";";
      }
    }
    if (i != trs.length - 1) {
      resultString += "\n";
    }
  }
  textarea.textContent = resultString;
  textarea.setAttribute("rows", trs.length - 1);
 }