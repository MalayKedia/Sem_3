var get_data_area = function () {
  return $("#data_area");
}

/* More about syntax: http://www.graphviz.org/doc/info/lang.html */
var parse = function() {
  var description = get_data_area().val();
  if (typeof(description) == "undefined" ||
    description === "")
    return undefined;
  var lines = description.split("\n");
  var result = [];
  var directed = $("#graph_type").val() === "digraph";
  var sep = directed ? "->" : "--";
  var ignore_the_first_line = $("#first_line_checkbox").is(":checked");
  var use_labels = $("#use_labels_checkbox").is(":checked");
  for (var i in lines) {
    if (ignore_the_first_line) {
      ignore_the_first_line = false;
      continue;
    }
    var line = lines[i].trim();
    if (line.length < 1 || line[0] === "#") {
      continue;
    }
    var elems = line.split(/\s+/);
    if (elems.length < 2)
      return undefined;
    var from = elems[0];
    var to = elems[1];
    var edge = from + sep + to;
    if (use_labels && elems.length > 2)
      edge += "[label=\"" + elems[2] + "\"]";
    result.push(edge);
  }
  return (directed ? "digraph" : "graph") + "{" + result.join(";") + "}";
}

/* Query example: https://draw.khairulin.com/chart?cht=gv&chl=digraph{1->2;2->3;1->3;3->4;1->5} */
var render_service = "https://draw.khairulin.com/";
var previous_graph = "";

var chart_url = function(graph) {
  var result = render_service + "chart?cht=gv&chl=" + graph;
  /*console.log("url: " + result);*/
  return result;
}

var clear_error = function () {
  var small = $("#error_message");
  small.html("")
  small.removeClass("error");
}

var report_error = function(message) {
  var small = $("#error_message");
  small.html(message);
  small.addClass("error");
}

var render_chart = function(graph) {
  if (graph !== previous_graph) {
    history.pushState({query: "graph"}, "graphpage", "?q=" + graph);
    $("#output").attr("src", chart_url(graph));
    previous_graph = graph;
  }
}

var show = function() {
  $("#show_button").attr("class", "success button expanded radius");
  clear_error();
  var graph = parse();
  if (graph)
    render_chart(graph);
  else
    report_error("unable to parse data");
  $("#show_button").attr("class", "success hollow button expanded radius");
}

var parse_url_query = function() {
  var url = window.location.href;
  var hash = url.indexOf("#");
  if (hash >= 0)
    url = url.substr(0, hash);
  var qmark = url.indexOf("?");
  if (qmark < 0)
    return "";
  var args = decodeURI(url.substr(qmark + 1)).split("&");
  for (var i in args) {
    var pair = args[i].split("=");
    if (pair.length >= 2 && pair[0] === "q")
      return pair.slice(1).join("=");
  }
  return "";
}

var handle_query = function () {
  var query = parse_url_query();
  if (query.length > 0 && query[query.length - 1] === "}") {
    var graph_type = "";
    var data = "";
    if (query.substr(0, 6) === "graph{") {
      graph_type = "graph";
      data = query.substr(6, query.length - 7);
    } else if (query.substr(0, 8) === "digraph{") {
      graph_type = "digraph";
      data = query.substr(8, query.length - 9);
    } else {
      return;
    }
    $("#graph_type").val(graph_type);
    var separator = graph_type === "graph" ? "--" : "->";
    var edges = data.split(";");
    var lines = [];
    var pattern = "[label";
    for (var i in edges) {
      var e = edges[i];
      if (e.length < 1)
        continue;
      var sep = e.indexOf(separator);
      if (sep < 1)
        continue;
      var line = e.substr(0, sep);
      var brace = e.indexOf("[", sep + 3);
      if (brace < 0) {
        line += " " + e.substr(sep + 2);
        lines.push(line);
        continue;
      }
      line += " " + e.substr(sep + 2, brace - sep - 2);
      if (e.substr(e.length - 2) === "\"]"
          && e.substr(brace + 1, 6) !== "label=\"") {
        line += " " + e.substr(brace + 8, e.length - brace - 10)
      }
      lines.push(line);
    }
    if (lines.length > 0) {
      get_data_area().val(lines.join("\n"));
      show();
    }
  }
}

var on_copy_button_click = function () {
  var data_area = get_data_area().get(0);
  data_area.select();
  data_area.setSelectionRange(0, 99999); /*For mobile devices*/
  document.execCommand("copy");
}

$(document).ready(function() {
  $("#show_button").click(show);
  $("#copy_button").click(on_copy_button_click);
  shortcut.add("Ctrl+Enter", show);
  handle_query();
});
