const express = require('express')
const app = express()
const port = 3000

const bodyParser = require('body-parser');

//To parse URL encoded data
app.use(bodyParser.urlencoded({ extended: false }))

//To parse json data
app.use(bodyParser.json())

// include statics
app.use(express.static(__dirname + "/public"));

app.set('view engine', 'pug')
app.set('views','./views');

const web_app_router = require("./js/routes/web_app");
const db_controller = require("./js/controller/db_controller");

// REST endpoints

// get all notes
app.get('/note', (req, res) => {
    res.end(db_controller.get_notes());
    db_controller.get_notes().then((r => {
        res.end(JSON.parse(r));
    }));
})

// get note by id
app.get('/note/:id', (req, res) => {
    db_controller.get_note_by_id(req.params.id).then((r) => {
        res.end(JSON.parse(r));
    })
})

// create new note
app.post('/note', (req, res) => {
    let title = req.body.title;
    let data = req.body.data;
    const object_data = {
        "title": title,
        "data": data
    }
    db_controller.add_note(object_data);
    res.sendStatus(200);
})

// actualize note by id
app.put('/note/:id', (req, res) => {

})

// delete note by id
app.delete('/note/:id', (req, res) => {
    res.end();
})

// add router for web app interface
app.use("/web_app", web_app_router);


app.listen(port, () => {
    console.log(`Listening on port ${port}`)
})