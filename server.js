var express = require('express');
var app = express();
 
var people = 1;

app.get('/', function (req, res) {
  res.status(200).send('<h2>Hello World!</h2>');
});
 
app.get("/brightness", function(req, res) {
  var r = req.query.r;
  var brightness = 500 - r;

  if (people == 0){
	res.status(200).send(0);
  	console.log("Nobody's at home. Turn off the light.");
  } 
  else{
	if (brightness >= 255) {
		console.log("周遭亮度: " + r);
		console.log("回傳亮度: " + 255);
  		res.status(200).send((255).toString());
 	 } 
	else if(brightness <= 0) {
  		console.log("周遭亮度: " + r);
		console.log("回傳亮度: " + 0); 
  		res.status(200).send((0).toString());
 	 }
	else {
		console.log("周遭亮度" + r);
		console.log("回傳亮度" + brightness);
		res.status(200).send((brightness).toString());
	}
  }
});

app.get("/people", function(req, res){
  var r = req.query.r;

  if (r == -1){
	if (people == 0){
		console.log("Error: 已經沒人在房間內!");
		res.status(200).send("-1 Error");
	}
	else{
  		people = people - 1;
  		console.log("一人離開房間 房間內剩餘" + people + "人");
		res.status(200).send("-1 Okay");
	}
 }	
  else if (r == 1){
  	people = people + 1;
  	console.log("一人進入房間 房間內剩餘" + people + "人");
	res.status(200).send("+1 Okay");
 }	
  else{
	res.status(200).send("Error");
 }

})

 
var server = app.listen(80, function () {
  console.log('伺服器在80埠開工了！');
});
