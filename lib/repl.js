var net   = require('net');
var repl  = require('repl');

var heap  = require('./heap');

exports.createRepl = createRepl;
exports.Repl = Repl;

function Repl(config) {
  config = config || {};

  var that = this;
  this.event = config.event || 'SIGUSR2',
  this.host = config.host || 'localhost';
  this.port = config.port || 9999;
  this.prompt = config.prompt || 'prof> ';
  this._listens = false;
  this._srv = net.createServer({ allowHalfOpen: false });

  this._srv.on('connection', this._connectionHandler.bind(this));
  this._srv.on('close', function() {
    that._listens = false;
    console.log('Debug server stopped');
  });

  process.on(this.event, this._eventHandler.bind(this));
}

Repl.prototype._connectionHandler = function(sock) {
  var session = repl.start(this.prompt, sock, null, true, false);

  session.context.heap = heap; 
};

Repl.prototype._eventHandler = function() {
  var that = this;

  if (this._listens) {
    this._srv.close();
  } else {
    this._srv.listen(this.port, this.host, function() {
      that._listens = true;

      console.log('Debug server listening on %s:%d', that.host, that.port);
    });
  }
};

function createRepl(config) {
  new Repl(config);
}
