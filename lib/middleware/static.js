var url = require('url');

exports.connect = handler;

function handler(config) {
  var prefix = new RegExp('^/' + (config.prefix || 'inspector') + '/');
  var files = config.files || [
    'Inspector.json',
    'debug.html',
    'overrides.js'
  ];

  return function(req, res, next) {
    var file = url.parse(req.url).path.split('/').pop();

    if (!prefix.test(req.url) && files.indexOf(file) === -1) {
      req.url = '/inspector' + req.url;
    }

    next();
  }
}
