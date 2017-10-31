"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
var monitors = setInterval(function() {
	sendCommand("volume_monitor", "getVolume\n");
	sendCommand("tempo_monitor", "getTempo\n");
	sendCommand("beat_monitor", "getBeat\n");
}, 1000)


$(document).ready(function() {

	$('#help').click(function(){
		sendCommand("prime", "help\n");
	});
	$('#volUp').click(function(){
		sendCommand("prime", "volumeI\n");
	});
	$('#volDown').click(function(){
		sendCommand("prime", "volumeD\n");
	});
	$('#tempoUp').click(function(){
		sendCommand("prime", "tempoI\n");
	});
	$('#tempoDown').click(function(){
		sendCommand("prime", "tempoD\n");
	});
	$('#beatNext').click(function(){
		sendCommand("prime", "beatN\n");
	});
	$('#beatPrev').click(function(){
		sendCommand("prime", "beatP\n");
	});
	$('#btnStop').click(function(){
		sendCommand("prime", "stop\n");
	});
	
	socket.on('commandReply', function(result) {
		var newDiv = $('<div></div>').text(result);
		$('#console').append(newDiv);
		$('#console').scrollTop($('#console').prop('scrollHeight'));
	});
	socket.on('volume_monitor_reply', function(result) {
			updateMonitor("#currentVolume", result);
		});
	socket.on('tempo_monitor_reply', function(result) {
			updateMonitor("#currentTempo", result);
		});
});

function updateMonitor(key, value) {
	var newDiv = $('<span></span>').text(value);
	$(key).html(newDiv);
}

function sendCommand(command, message) {
	socket.emit(command, message);
};
