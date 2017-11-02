"use strict";
// Client-side interactions with the browser.

// Websocket connection to server
var socket = io.connect();

// Make connection to server when web page is fully loaded.
$(document).ready(function() {
	console.log("Document loaded");
	
	// Send message to request some (one-shot) updates:
	sendRequest('cpuinfo');
	sendRequest('version');
	sendRequest('cmdline');

	// Setup a repeating function (every 1s)
	window.setInterval(function() {sendRequest('uptime')}, 1000);


	// Handle data coming back from the server
	socket.on('fileContents', function(result) {
		var fileName = result.fileName;
		var contents = result.contents;
//		console.log("fileContenst callback: fileName " + fileName 
//				+ ", contents: " + contents);
		
		var domObj;
		switch(fileName) {
		case 'version':
			domObj = $('#versionId');
			break;
		case 'uptime':
			domObj = $('#uptimeId');
			break;
		case 'cpuinfo':
			domObj = $('#cpuinfoId');
			break;
		case 'cmdline':
			domObj = $('#cmdlineId');
			break;
		default:
			console.log("Unknown DOM object: " + fileName);
			return;
		}
		// Make linefeeds into <br> tag.
		contents = replaceAll(contents, "\n", "<br/>");
		domObj.html(contents);
	});
	
});

function sendRequest(file) {
	console.log("Requesting '" + file + "'");
	socket.emit('proc', file);
}

function replaceAll(str, find, replace) {
	return str.replace(new RegExp(find, 'g'), replace);
}
