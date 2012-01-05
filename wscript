blddir  = "build"
srcdir  = "."
APPNAME = "profiler"
VERSION = "0.0.1"

def set_options(ctx):
  ctx.tool_options("compiler_cxx")

def configure(ctx):
  ctx.define("Name", "profiler")
  ctx.check_tool("compiler_cxx")
  ctx.check_tool("node_addon")

def build(ctx):
  t = ctx.new_task_gen("cxx", "shlib", "node_addon")
  t.target = "profiler"
  t.source = """
    src/graph_edge.cc
    src/graph_node.cc
    src/profiler.cc
    src/snapshot.cc
  """
