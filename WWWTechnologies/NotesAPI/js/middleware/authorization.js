const express = require('express')

const jsonwt = require('jsonwebtoken')
require("dotenv").config();
const db_controller = require("./../controller/db_controller")

const cookieParser = require('cookie-parser');


module.exports = {
    authorize: authorizeToken = (req, res, next) => {
        if(!req.cookies.jwt) {
            return next(new Error("Unauthorized."));
        }
        const token = req.cookies.jwt;
        if(!token) {
            return next(new Error("Missing token."));
        }

        try {
            jsonwt.verify(token, process.env.JWT_SECRET);
            next();
        } catch(err) {
            return next(err);
        }
    },

    authorize_header: function(req, res, next) {
        if(!req.header.authorization) {
            return res.sendStatus(401);
        }
        const token = req.header["authorization"].split(" ")[1];
        if(!token) {
            return res.sendStatus(401);
        }

        try {
            jsonwt.verify(token, process.env.JWT_SECRET);
            next();
        } catch(err) {
            return res.sendStatus(401);
        }
    }
}