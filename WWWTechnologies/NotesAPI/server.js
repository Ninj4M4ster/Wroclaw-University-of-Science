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
const authorization = require("./js/middleware/authorization");
const jsonwt = require('jsonwebtoken');
const bcrypt = require("bcryptjs");

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
    db_controller.get_note_by_title(req.params.id).then((r) => {
        res.end(JSON.parse(r));
    })
})

// create new note
app.post('/note',
    authorization.authorize_header,
    (req, res) => {
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
app.put('/note/:id',
    authorization.authorize_header,
    (req, res) => {
    db_controller.update_note(req.params.id, req.body.title, req.body.data).then((r) => {
        if(r === 0) {
            res.sendStatus(400);
        } else {
            res.sendStatus(200);
        }
    })
})

// delete note by id
app.delete('/note/:id',
    authorization.authorize_header,
    (req, res) => {
    db_controller.delete_note(req.params.id).then((r) => {
        if(r === 0) {
            res.sendStatus(400);
        } else {
            res.sendStatus(200);
        }
    })
})

// login to get token
app.post("/login",
    (req, res) => {
        const user = req.body;
        if(!user.login || !user.password) {
            return res.sendStatus(401);
        }
        db_controller.login_user(user.login).then((result) => {
            bcrypt.compare(
                user.password,
                result.password
            ).then(() => {
                const token = jsonwt.sign({ user }, process.env.JWT_SECRET, {
                    expiresIn: "1h"
                });
                res.json({ token });
            }).catch(() => {
                return res.sendStatus(401);
            })
        }).catch((err) => {
            return res.send(err);
        })
    });

// register to database
app.post("/register", async (req, res) => {
    if(!req.body.login || !req.body.password) {
        return res.sendStatus(401);
    }
    const hash = await bcrypt.hash(req.body.password, 10);
    const user = req.body;
    user.password = hash;
    db_controller.register_user(user.login, user.password).then(() => {
        const token = jsonwt.sign({ user }, process.env.JWT_SECRET, {
            expiresIn: "1h"
        });
        return res.json({ token });
    }).catch((error) => {
        res.send(error);
    })
})

// add router for web app interface
app.use("/web_app", web_app_router);


app.listen(port, () => {
    console.log(`Listening on port ${port}`)
})