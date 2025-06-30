> library(tidyverse)
> library(igraph)
> library(ggraph)
> library(tidygraph)

> type_data <- read.csv(file.choose(),stringsAsFactors = FALSE)
> graph <- graph_from_data_frame(type_data,directed=TRUE)
> graph_tbl <-as_tbl_graph(graph)
> edgecolors <- c("0"="black","0.5"="blue","1"="gray","2"="red")
> ggraph(graph_tbl,layout="circle")+geom_edge_link(aes(color=as.factor(Multiplier)),arrow=arrow(length=unit(3,'mm')),end_cap=circle(2,'mm'))+scale_edge_color_manual(values=edgecolors)+geom_node_text(aes(label=name))+theme_void()

> strength(graph,mode="in",weights=E(graph)$Multiplier)
Normal     Fire    Water Electric    Grass 
14.0     15.5     14.5     14.0     17.0 
Ice Fighting   Poison   Ground   Flying 
16.5     15.0     15.5     15.0     14.5 
Psychic      Bug     Rock    Ghost   Dragon 
13.0     16.5     16.0     12.0     13.0 

> strength(graph,mode="out",weights=E(graph)$Multiplier)
Normal     Fire    Water Electric    Grass 
13.5     16.0     16.5     14.5     15.0 
Ice Fighting   Poison   Ground   Flying 
18.0     15.0     15.0     17.0     17.0 
Psychic      Bug     Rock    Ghost   Dragon 
16.5     16.0     18.0     14.0      0.0 

> type_between <- betweenness(graph,directed=TRUE, weight=1/E(graph)$Multiplier)
> sort(type_between,decreasing=TRUE)
Ghost       Grass         Ice 
26841.89216  6751.84521  3377.98761 
Fire      Poison       Water 
1684.16662   907.21025   422.47657 
Electric      Normal         Bug 
210.65306   104.29199    92.58768 
Psychic      Ground        Rock 
44.56928    19.88763    14.03428 
Fighting      Flying      Dragon 
10.21990     5.82500     0.00000 
       
> type_eigenvector <- eigen_centrality(graph,directed = TRUE,weights=E(graph)$Multiplier)$vector
> sort(type_eigenvector,decreasing=TRUE)
Grass       Ice       Bug      Rock 
1.0000000 0.9618063 0.9610983 0.9381498 
Poison      Fire    Ground  Fighting 
0.8972853 0.8968487 0.8856015 0.8588297 
Water    Flying    Normal  Electric 
0.8451698 0.8422525 0.8256510 0.8177788 
Psychic    Dragon     Ghost 
0.7778451 0.7594506 0.6853283 

> in_degree <- strength(graph,mode="in",weights=E(graph)$Multiplier)
> out_degree <- strength(graph,mode="out",weights=E(graph)$Multiplier)
> degree_data <- tibble(Type=names(in_degree),InDegree=as.numeric(in_degree),OutDegree=as.numeric(out_degree)) %>% mutate(TotalDegree=InDegree+OutDegree)
> ggplot(degree_data,aes(x=InDegree,y=OutDegree,label=Type))+geom_point(color="steelblue",size=3)+geom_text(vjust=-0.5,size=3)+theme_minimal()+labs(x="InDegree",y="OutDegree")

> bet_vec_data <- tibble(Type=names(type_between),Betweenness=as.numeric(type_between),Eigenvector=as.numeric(type_eigenvector))
> ggplot(bet_vec_data,aes(x=Eigenvector,y=Betweenness,label=Type))+geom_point(color="darkorange",size=3)+geom_text(vjust=-0.5,size=3)+theme_minimal()+labs(x="Eigenvector",y="Betweenness")

       