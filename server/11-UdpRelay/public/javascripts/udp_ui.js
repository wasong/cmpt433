"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	$('#btnCount').click(function(){
		sendPrimeCommand("help\n");
	});
	$('#btnFirst').click(function(){
		sendPrimeCommand("volume+\n");
	});
	$('#btnLast').click(function(){
		sendPrimeCommand("volume-\n");
	});
	$('#btnStop').click(function(){
		sendPrimeCommand("stop\n");
	});
	
	socket.on('commandReply', function(result) {
		var newDiv = $('<div></div>').text(result);
		$('#messages').append(newDiv);
		$('#messages').scrollTop($('#messages').prop('scrollHeight'));
	});
	
});

function sendPrimeCommand(message) {
	socket.emit('prime', message);
};
