import "memory/memory.clp".
import "base/cilcfg.clp".
import "base/utility.clp".
analyze session_name("cil_body").

% Following does dotgraph generation for memory analysis.
% base/cfgdot.clp has been carried over and changed for memory analysis dotgraph because guarddot.clp and valdot.clp analysis/memory 
% throw bad symbol error for dotgraph. Node type is still cfg_node.
% - Srinivasan Kannan 10March2016

using dotty.

% add to label points in the graph as FILE:LINE rather than PP
predicate dot_point_locations().

% use NAME instead of foo_memory for the dotty file
predicate dot_memory_name(NAME:string).

% Remove special characters from a filename so dotty doesn't complain.
predicate dot_filename_sanitize(in string, out string) succeeds [once].

% Dotty graph

type dg_node_label ::=
    dg_memory_node{pp}
  | dg_lab_node{pp, cfg_node}.

predicate dotty_node(dg_node_label, list[t_dg_attr]).
predicate dotty_edge(dg_node_label, dg_node_label, list[t_dg_attr]).

dotty_graph(Name, true, dotgraph{Nodes, Edges}, [], NodeAttrs, []) :-
    ( dot_memory_name(Name)
    ; ~dot_memory_name(_), 
      cil_curfn(Fn), 
      ( cil_cursum(Sum), Name0 = Fn ^ "_" ^ tostring(Sum) ^ "_cfg"
      ; ~cil_cursum(_), Name0 = Fn ^ "_cfg"
      ),
      Name = filename_sanitize(Name0)
    ),
    \/(dotty_node(NN, NAs), N = dg_node{NN, NAs}):list_all(N, Nodes),
    \/(dotty_edge(EN1, EN2, EAs), E = dg_edge{EN1, EN2, EAs})
        :list_all(E, Edges),
    % Color all the graph nodes using global attributes
    NodeAttrs = [dg_attr{"color", "green"}, dg_attr{"style", "filled"}].
    

% add labels for special CFG nodes
dotty_node(dg_lab_node{P, N}, Attrs) :-
    cfgn_final(P, N),
    Attrs = [dg_attr{"shape", "box"}, dg_attr{"color", "cyan"},
	     dg_attr{"label", tostring(N)}].

dotty_edge(dg_lab_node{P, N}, dg_memory_node{P}, []) :-
    cfgn_final(P, N).

   
% add edges and label attributes for CFG edges
dotty_node(dg_memory_node{P}, [dg_attr{"label", Label}]) :-
    (cfge_final(P,_,_) ; cfge_final(_,P,_)),
    (
        dot_point_locations(),
        point_location(P, File, Line), location_string(File, Line, Label)
    ;
        ~dot_point_locations(),
        Label = tostring(P)
    ).

dotty_edge(dg_memory_node{P0}, dg_memory_node{P1}, Attrs) :-
    cfge_final(P0,P1,_), 
    \/cfge_final(P0,P1,E):list_all(E,Es),
    Attrs = [dg_attr{"label", tostring(Es)}].

