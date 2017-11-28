"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
// var socket = io.connect();

var imagePos = 0
var url = "https://localhost:8088/grabber0"

$(document).ready(function() {
	$("#getImage").click(function() {
		setInterval(showImages, 250)
	})
});

function showImages() {
	if (imagePos < 19) {
		imagePos += 1
		setImage()
	} else {
		imagePos = 1
		setImage()
	}
}

function setImage() {
	var path = imagePos < 10 ?
	url + "0" + imagePos + ".jpeg" :
	url + imagePos + ".jpeg"

	$("#webcam").attr("src", path)
}

