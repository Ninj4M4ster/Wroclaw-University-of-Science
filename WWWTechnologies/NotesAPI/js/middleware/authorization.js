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
            const decoded = jsonwt.verify(token, process.env.JWT_SECRET);
            next();
        } catch(err) {
            return next(err);
        }
    }
}