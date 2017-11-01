"use strict";
// Client-side interactions with the browser.

// Web sockets: automatically establish a socket with the server
var socket = io.connect();

// Make connection to server when web page is fully loaded.
$(document).ready(function() {

	// Setup a repeating function (every 1s)
	window.setInterval(function() {sendRequest('uptime')}, 1000);

	$('#modeNone').click(function(){
		sendUDPCommand("beat:0\n");
	});
	$('#modeRock1').click(function(){
		sendUDPCommand("beat:1\n");
	});
	$('#modeRock2').click(function(){
		sendUDPCommand("beat:2\n");
	});

	$('#volumeDown').click(function(){
		sendUDPCommand("volume-\n");
	});
	$('#volumeUp').click(function(){
		sendUDPCommand("volume+\n");
	});
	
	$('#tempoDown').click(function(){
		sendUDPCommand("tempo-\n");
	});
	$('#tempoUp').click(function(){
		sendUDPCommand("tempo+\n");
	});

	$('#hi-hat').click(function(){
		sendUDPCommand("hi-hat\n");
	});
	$('#snare').click(function(){
		sendUDPCommand("snare\n");
	});
	$('#bass').click(function(){
		sendUDPCommand("bass\n");
	});

	// Handle data coming back from the server
	socket.on('newBeat', function(result) {
		$('#modeid').html(result);
	});

	socket.on('newVolume', function(result) {
		$('#volumeid').val(result);
	});

	socket.on('newTempo', function(result) {
		$('#tempoid').val(result);
	});

	socket.on('newSound', function(result) {
		console.log('Played sound: ' + result);
	});

	socket.on('fileContents', function(result) {
		var contents = result.contents;
		
		// Make linefeeds into <br> tag.
		contents = replaceAll(contents, "\n", "<br/>");
		var uptimeHours = Math.trunc((Number(contents.substring(0, contents.lastIndexOf(" ")))/60/60) % 24);
		var uptimeMinutes = Math.trunc((Number(contents.substring(0, contents.lastIndexOf(" ")))/60) % 60);
		var uptimeSeconds = Math.trunc(Number(contents.substring(0, contents.lastIndexOf(" "))) % 60);
		$('#uptimeId').html('<br/>' + formatClock(uptimeHours) + ':' + formatClock(uptimeMinutes.toString())
					+ ':' + formatClock(uptimeSeconds));
	});
});

function sendUDPCommand(message) {
	socket.emit('udp', message);
}

function sendRequest(file) {
	console.log("Requesting '" + file + "'");
	socket.emit('proc', file);
}

function replaceAll(str, find, replace) {
	return str.replace(new RegExp(find, 'g'), replace);
}

function formatClock(digit) {
	return (digit < 10) ? '0' + digit.toString() : digit.toString();
}