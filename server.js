var express = require('express')
 , bodyParser=require('body-parser');

var qs = require('querystring');

var app = express();
app.use(bodyParser.json()); 
var people = 0;
var phone = (0).toString;
var phonelight = (0).toString;
app.get('/', function (req, res) {
  res.status(200).send('<h2>Hello World!</h2>');
});


app.post('/',function(req, res){    
  console.log("mode: "+req.body.mode);
  console.log("light: "+req.body.light);
  phone = req.body.mode;
  phonelight = req.body.light;
});
 
app.get("/brightness", function(req, res) {
  var r = req.query.r;
  if(phone == (0).toString()){
    if (people == 0){
	res.status(200).send((0).toString());
  	console.log("Nobody's at home. Turn off the light.");
    } 
    else if(0 < r && r < 333){	
	console.log("周遭亮度: " + r);
	console.log("回傳亮度: " + 255);
	res.status(200).send((255).toString());
    } 
    else if(r < 666){
	console.log("周遭亮度: " + r);
  	console.log("回傳亮度: " + 170);
	res.status(200).send((170).toString());
    } 
    else if(r < 999){
	console.log("周遭亮度: " + r);
	console.log("回傳亮度: " + 85);
	res.status(200).send((85).toString());
    }
    else {
	console.log("周遭亮度: " + r);
	console.log("回傳亮度: " + 0);
	res.status(200).send((0).toString());
    }   
  }
  else{
   	if(phonelight == (0).toString()){
		console.log("手機指定: 0");
		res.status(200).send((0).toString());
	}     
	else if(phonelight == (1).toString()){
		console.log("手機指定: 85");
		res.status(200).send((85).toString());
	}
	else if(phonelight == (2).toString()){
		console.log("手機指定: 170");
		res.status(200).send((170).toString());
	}
	else if(phonelight == (3).toString()){
		console.log("手機指定: 255");
		res.status(200).send((255).toString());
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

});

 
var server = app.listen(80, function () {
  console.log('伺服器在80埠開工了！');
});
