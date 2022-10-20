const express = require("express")
const request = require("request")
const bodyParser = require("body-parser")
const https = require("https")
const app = express()


app.use(bodyParser.urlencoded({extended:true}))
app.use(express.static("public"))



app.get("/",function(req,res){
  res.sendFile(__dirname  +"/signup.html")
})

app.post("/",function (req,res){
  const name = req.body.myName
  const lastName = req.body.myLastName
  const email = req.body.myEmail

  var data = {
      members:[
        {
          email_address: email,
          status:"subscribed",
          merge_fields:{
            FNAME: name,
            LNAME: lastName
          }
        }
      ]
  };

  var jsonData = JSON.stringify(data)

  const url = "https://us8.api.mailchimp.com/3.0/lists/64e720b8ba"

  const options = {
    method:"POST",
    auth: "bam1:da7d80a502223ec070e81a70570c1fe7-us8"
  }

  const request = https.request(url,options,function(response){
    response.on("data",function(data){
    if(response.statusCode ===200){
      res.sendFile(__dirname + "/success.html")
    } else{
      res.sendFile(__dirname + "/failure.html")
    }

    });
  });
  request.write(jsonData);
  request.end();

});


app.post("/failure",function(req,res){
  res.redirect("/")
});

app.listen(process.env.PORT || 3000,function(){
  console.log("server is up and running")
})
