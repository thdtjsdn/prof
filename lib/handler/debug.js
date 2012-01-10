var url = require('url');

exports.connect = handler;

function handler(config) {
  return function(req, res, next) {
    req.url = '/debug.html';

    next();
  }
}
