"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	$('#help').click(function(){
		sendPrimeCommand("help\n");
	});
	$('#volUp').click(function(){
		sendPrimeCommand("volumeI\n");
	});
	$('#volDown').click(function(){
		sendPrimeCommand("volumeD\n");
	});
	$('#tempoUp').click(function(){
		sendPrimeCommand("tempoI\n");
	});
	$('#tempoDown').click(function(){
		sendPrimeCommand("tempoD\n");
	});
	$('#beatNext').click(function(){
		sendPrimeCommand("beatN\n");
	});
	$('#beatPrev').click(function(){
		sendPrimeCommand("beatP\n");
	});
	$('#btnStop').click(function(){
		sendPrimeCommand("stop\n");
	});
	
	socket.on('commandReply', function(result) {
		var newDiv = $('<div></div>').text(result);
		$('#console').append(newDiv);
		$('#console.').scrollTop($('#messages').prop('scrollHeight'));
	});
	
});

function sendPrimeCommand(message) {
	socket.emit('prime', message);
};
