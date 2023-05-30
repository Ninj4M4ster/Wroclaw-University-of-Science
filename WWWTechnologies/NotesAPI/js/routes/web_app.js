const express = require('express')
const router = express.Router();

const bodyParser = require('body-parser');

const db_controller = require("./../controller/db_controller");
const authorization = require("./../middleware/authorization");
const bcrypt = require("bcryptjs");
const jsonwt = require('jsonwebtoken');
require("dotenv").config();

const cookieParser = require('cookie-parser');

// web app endpoints
router.use(express.static(__dirname + "/public"));
router.use(cookieParser());

const auth_err_handler = (err, req, res, next) => {
    if(err) {
        return res.redirect("/web_app/login");
    }
    return next();
}

// login page
router.get('/login', (req, res) => {
    res.render("login_page");
})

// login to database
router.post("/login", (req, res) => {
    if(!req.body.login || !req.body.password) {
        res.redirect("/web_app/login");
    }
    const user = req.body;
    db_controller.login_user(user.login).then((result) => {
        bcrypt.compare(
            user.password,
            result.password
        ).then(() => {
            const token = jsonwt.sign({ user }, process.env.JWT_SECRET, {
                expiresIn: "1h",
            });
            res.cookie("jwt", token);
            res.redirect("/web_app/note");
        }).catch(() => {
            res.redirect("/web_app/login");
        })
    }).catch((err) => {
        res.redirect("/web_app/login");
    })
})

// get register page
router.get('/register', (req, res) => {
    res.render("register_page");
})

// register to API
router.post("/register", async (req, res) => {
    if(!req.body.login || !req.body.password) {
        res.redirect("/web_app/register");
    }
    const hash = await bcrypt.hash(req.body.password, 10);
    const user = req.body;
    user.password = hash;
    db_controller.register_user(user.login, user.password).then(() => {
        const token = jsonwt.sign({ user }, process.env.JWT_SECRET, {
            expiresIn: "1h"
        });
        res.cookie("jwt", token);
        res.redirect("/web_app/note");
    }).catch((error) => {
        res.redirect("/web_app/register");
    })
})

// get all notes
router.get('/note', (req, res) => {
    db_controller.get_notes().then((r => {
        res.render('all_notes', {
            notes: JSON.parse(r)
        });
    }));
});

// get add new note page
router.get('/add_new_note',
    authorization.authorize,
    auth_err_handler,
    (req, res) => {
    res.render('add_new_note');
});

// add new note
router.post("/new_note",
    authorization.authorize,
    auth_err_handler,
    (req, res) => {
    let title = req.body.title;
    let data = req.body.data;
    const object_data = {
        "title": title,
        "data": data
    }
    db_controller.add_note(object_data);
    res.redirect("/web_app/note");
});

// get note by id
router.get('/note/:id', (req, res) => {
    db_controller.get_note_by_title(req.params.id).then((r) => {
        const note = JSON.parse(r);
        if(Object.keys(note).length !== 0) {
            res.render('note', {
                note: note
            })
        } else {
            res.redirect("/web_app/note");
        }
    });
});

// send data to search for a note
router.post("/note/find_note", (req, res) => {
    let title = req.body.searched_title;
    res.redirect(`/web_app/note/${title}`);
})

// delete given note by title
router.post("/delete_note/:id",
    authorization.authorize,
    auth_err_handler,
    (req, res) => {
    db_controller.delete_note(req.params.id).then((deletedCount) => {
        let status;
        if(deletedCount === 0) {
            status = "Could not delete a note.";
        } else {
            status = "Successfully deleted a note.";
        }
        res.redirect('/web_app/note');
    });
})

// update given note
router.post("/note/update_note",
    authorization.authorize,
    auth_err_handler,
    (req,
     res) => {
    db_controller.update_note(req.body.prev_title,
        req.body.note_title,
        req.body.note_data).then((modified_count) => {
            let status;
            if(modified_count === 0) {
                status = "Not modified.";
            } else {
                status = "Successfully updated note.";
            }

            res.redirect(`/web_app/note`);
    })
})


module.exports = router;