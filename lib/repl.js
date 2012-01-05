var net       = require('net');
var repl      = require('repl');
var profiler  = require('../index');

var prompt    = 'prof> ';
var srv       = net.createServer({ allowHalfOpen: false });
var listens   = false;

srv.on('connection', function(socket) {
  var session = repl.start(prompt, socket, null, true, false);

  console.dir(session)
  session.context['heap'] = profiler.heap;
});
srv.on('close', function() {
  listens = false;
  console.log('Debug server stopped');
});

process.on('SIGUSR2', function() {
  if (listens) {
    srv.close();
  } else {
    srv.listen(9999, '0.0.0.0', function() {
      listens = true;

      console.log('Debug server listening');
    });
  }
});
