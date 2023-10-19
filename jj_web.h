    INIReader reader("serverconfig.ini");
    std::string e_ns = reader.Get("server", "Ns", "-");
    std::string e_ho = reader.Get("server", "Host", "-");
    std::string e_ip = reader.Get("server", "Ip", "-");
    std::string e_type = reader.Get("server", "Type", "-");
    std::string e_mail = reader.Get("server", "Mail", "-");
    std::string e_port = reader.Get("server", "Port", "-");
    std::string e_webport = reader.Get("server", "Webport", "-");

//home
  auto say_index = [](const HttpRequest& request) -> HttpResponse {

    HttpResponse response(HttpStatusCode::Ok);
    std::string content;
    content += "<!doctype html><html>";
    content += "<head><meta><style>body{margin:0}ul{list-style-type:none;margin:0;padding:0;width:25%;background-color:#56abe5;position:fixed;height:100%;overflow:auto}li a{display:block;color:#000;padding:8px 16px;text-decoration:none}li a.active{background-color:#012650;color:white}li a:hover:not(.active){background-color:#0f3763;color:white}</style></head>";
    content += "<body><ul>";
    content += "<li><b><a class='active' href='/'>HOME</a></b></li>";
    content += "<li><b><a href='nodes.html'>NODES</a></b></li>";
    content += "<li><b><a href='seeds.html'>SEEDS</a></b></li>";
    content += "<li><b><a href='system.html'>SYSTEM</a></b></li>";
    content += "<li><b><a href='statistics.html'>STATISTICS</a></b></li>";
    content += "<li><b><a href='https://digibyte.help' target='_blank'>Help</a></b></li>";
    content += "</ul>";
    content += "<div style='margin-left:25%;padding:1px 16px;height:1000px;'>";
    if(!fTestNet){ content += "<h1><b>" + e_ns + "</b></h1>\n\n"; }else{ content += "<h1><b>" + e_ns + " - ( Testnet )</b></h1>\n\n"; }
    content += "<p><b>NS:</b> " + e_ns + " ";
    content += "<a href=https://www.whatsmydns.net/#A/" + e_ns + ">A Check</a> - ";
    content += "<a href=https://www.whatsmydns.net/#NS/" + e_ns + ">NS Check</a></p>\n";
    content += "<p><b>IP:</b> " + e_ip + "</p>\n";
    content += "<p><b>Port:</b> " + e_port + "</p>\n";
    content += "<p><b>Host:</b> " + e_ho + " ";
    content += "<a href=https://www.whatsmydns.net/#A/" + e_ho + ">A Check</a></p>\n";
    content += "<p><b>Email:</b> " + e_mail + "</p>\n";
    content += "<p><b>Webport:</b> " + e_webport + "</p>\n";
    content += "</div>\n";
    content += "</body>\n</html>\n";
    response.SetHeader("Content-Type", "text/html");
    response.SetContent(content);
    return response;
    
};
//home
//Nodes
auto send_nodes = [](const HttpRequest& request) -> HttpResponse {

    vector<CAddrReport> v = db.GetAll();
    sort(v.begin(), v.end(), StatCompare);
    HttpResponse response(HttpStatusCode::Ok);
    std::string content;
    std::string xa = std::to_string(sa_Good);
    std::string xb = std::to_string(sa_Avail);
    std::string xc = std::to_string(sa_Tracked);
    std::string xd = std::to_string(sa_Age);
    std::string xe = std::to_string(sa_New);
    std::string xf = std::to_string(sa_AvailTrackedNew);
    std::string xg = std::to_string(sa_Banned);
    std::string xi = std::to_string(sa_requests);
    std::string xj = std::to_string(sa_queries);
    content += "<!doctype html><html>";
    content += "<head><meta><style>body{margin:0}ul{list-style-type:none;margin:0;padding:0;width:25%;background-color:#56abe5;position:fixed;height:100%;overflow:auto}li a{display:block;color:#000;padding:8px 16px;text-decoration:none}li a.active{background-color:#012650;color:white}li a:hover:not(.active){background-color:#0f3763;color:white}</style></head>";
    content += "<body><ul>";
    content += "<li><b><a href='/'>HOME</a></b></li>";
    content += "<li><b><a class='active' href='nodes.html'>NODES</a></b></li>";
    content += "<li><b><a href='seeds.html'>SEEDS</a></b></li>";
    content += "<li><b><a href='system.html'>SYSTEM</a></b></li>";
    content += "<li><b><a href='statistics.html'>STATISTICS</a></b></li>";
    content += "<li><b><a href='https://digibyte.help' target='_blank'>Help</a></b></li>";
    content += "</ul>";
    content += "<div style='margin-left:25%;padding:1px 16px;height:1000px;'>";
    if(!fTestNet){ content += "<h1><b>" + e_ns + "</b></h1>\n\n"; }else{ content += "<h1><b>" + e_ns + " - ( Testnet )</b></h1>\n\n"; }
    for (vector<CAddrReport>::const_iterator it = v.begin(); it < v.end(); it++) {
        CAddrReport rep = *it;
        time_t datetime = rep.lastSuccess;
        tm *local_time = localtime(&datetime);
        std::string tim_min = std::to_string(local_time->tm_min);
        std::string tim_h = std::to_string(1 + local_time->tm_hour);
        std::string tim_d = std::to_string(local_time->tm_mday);
        std::string tim_m = std::to_string(1 + local_time->tm_mon);
        std::string tim_y = std::to_string(1900 + local_time->tm_year);
        std::string xo = rep.ip.ToString().c_str();
        std::string xu = rep.clientSubVersion.c_str();
        std::string xq = std::to_string(rep.blocks);
        content += "<p><b>LastSuccess:</b> ";
        content += tim_h + ":" + tim_min + "|" + tim_d + "-" + tim_m + "-" + tim_y;
        content += " <b>Version:</b> " + xu + " -";
        content += " <b>Blocks:</b> " + xq + " <b>IP:</b> " + xo + "</p>\n";
      }
    content += "</div>\n";
    content += "</body>\n</html>\n";
    response.SetHeader("Content-Type", "text/html");
    response.SetContent(content);
    return response;
};
//Nodes
//Seeds
auto send_seeds = [](const HttpRequest& request) -> HttpResponse {

    HttpResponse response(HttpStatusCode::Ok);
    std::string content;
    std::string xa = std::to_string(sa_Good);
    std::string xb = std::to_string(sa_Avail);
    std::string xc = std::to_string(sa_Tracked);
    std::string xd = std::to_string(sa_Age);
    std::string xe = std::to_string(sa_New);
    std::string xf = std::to_string(sa_AvailTrackedNew);
    std::string xg = std::to_string(sa_Banned);
    std::string xi = std::to_string(sa_requests);
    std::string xj = std::to_string(sa_queries);
    content += "<!doctype html><html>";
    content += "<head><meta><style>body{margin:0}ul{list-style-type:none;margin:0;padding:0;width:25%;background-color:#56abe5;position:fixed;height:100%;overflow:auto}li a{display:block;color:#000;padding:8px 16px;text-decoration:none}li a.active{background-color:#012650;color:white}li a:hover:not(.active){background-color:#0f3763;color:white}</style></head>";
    content += "<body><ul>";
    content += "<li><b><a href='/'>HOME</a></b></li>";
    content += "<li><b><a href='nodes.html'>NODES</a></b></li>";
    content += "<li><b><a class='active' href='seeds.html'>SEEDS</a></b></li>";
    content += "<li><b><a href='system.html'>SYSTEM</a></b></li>";
    content += "<li><b><a href='statistics.html'>STATISTICS</a></b></li>";
    content += "<li><b><a href='https://digibyte.help' target='_blank'>Help</a></b></li>";
    content += "</ul>";
    content += "<div style='margin-left:25%;padding:1px 16px;height:1000px;'>";
    if(!fTestNet){ 
      //main
      content += "<h1><b>" + e_ns + "</b></h1>\n\n";
      for (int i = 0; seeds[i] != ""; i++){ 
          content += "<p><b>" + seeds[i] + "</b> ";
          content += "<a href=https://www.whatsmydns.net/#A/" + seeds[i] + ">A Check</a> - ";
          content += "<a href=https://www.whatsmydns.net/#NS/" + seeds[i] + ">NS Check</a></p>\n";           
      }  
    }else{ 
      //testnet
      content += "<h1><b>" + e_ns + " - ( Testnet )</b></h1>\n\n";
      for (int i = 0; testseeds[i] != ""; i++){
          content += "<p><b>" + testseeds[i] + "</b></p>\n";
          content += "<a href=https://www.whatsmydns.net/#A/" + testseeds[i] + ">A Check</a> - ";
          content += "<a href=https://www.whatsmydns.net/#NS/" + testseeds[i] + ">NS Check</a></p>\n";             
      }
    }
    content += "</div>\n";
    content += "</body>\n</html>\n";
    response.SetHeader("Content-Type", "text/html");
    response.SetContent(content);
    return response;
};
//Seeds
//system
auto send_system = [](const HttpRequest& request) -> HttpResponse {

    HttpResponse response(HttpStatusCode::Ok);
    std::string content;
    std::string xk = std::to_string(getcpu());
    std::string xl = std::to_string(getmemrss());
    std::string xm = std::to_string(getmemvsz());
    content += "<!doctype html><html>";
    content += "<head><meta><style>body{margin:0}ul{list-style-type:none;margin:0;padding:0;width:25%;background-color:#56abe5;position:fixed;height:100%;overflow:auto}li a{display:block;color:#000;padding:8px 16px;text-decoration:none}li a.active{background-color:#012650;color:white}li a:hover:not(.active){background-color:#0f3763;color:white}</style></head>";
    content += "<body><ul>";
    content += "<li><b><a href='/'>HOME</a></b></li>";
    content += "<li><b><a href='nodes.html'>NODES</a></b></li>";
    content += "<li><b><a href='seeds.html'>SEEDS</a></b></li>";
    content += "<li><b><a class='active' href='system.html'>SYSTEM</a></b></li>";
    content += "<li><b><a href='statistics.html'>STATISTICS</a></b></li>";
    content += "<li><b><a href='https://digibyte.help' target='_blank'>Help</a></b></li>";
    content += "</ul>";
    content += "<div style='margin-left:25%;padding:1px 16px;height:1000px;'>";
    if(!fTestNet){ content += "<h1><b>" + e_ns + "</b></h1>\n\n"; }else{ content += "<h1><b>" + e_ns + " - ( Testnet )</b></h1>\n\n"; }
    content += "<p><b>CPU:</b> " + xk + " % </p>\n";
    content += "<p><b>RSS:</b> " + xl + " MB </p>\n";
    content += "<p><b>VSZ:</b> " + xm + " MB </p>\n";
    content += "</div>\n";
    content += "</body>\n</html>\n";
    response.SetHeader("Content-Type", "text/html");
    response.SetContent(content);
    return response;
};
//system
//statistics
auto send_statistics = [](const HttpRequest& request) -> HttpResponse {

    HttpResponse response(HttpStatusCode::Ok);
    std::string content;
    std::string xa = std::to_string(sa_Good);
    std::string xb = std::to_string(sa_Avail);
    std::string xc = std::to_string(sa_Tracked);
    std::string xd = std::to_string(sa_Age);
    std::string xe = std::to_string(sa_New);
    std::string xf = std::to_string(sa_AvailTrackedNew);
    std::string xg = std::to_string(sa_Banned);
    std::string xi = std::to_string(sa_requests);
    std::string xj = std::to_string(sa_queries);
    content += "<!doctype html><html>";
    content += "<head><meta><style>body{margin:0}ul{list-style-type:none;margin:0;padding:0;width:25%;background-color:#56abe5;position:fixed;height:100%;overflow:auto}li a{display:block;color:#000;padding:8px 16px;text-decoration:none}li a.active{background-color:#012650;color:white}li a:hover:not(.active){background-color:#0f3763;color:white}</style></head>";
    content += "<body><ul>";
    content += "<li><b><a href='/'>HOME</a></b></li>";
    content += "<li><b><a href='nodes.html'>NODES</a></b></li>";
    content += "<li><b><a href='seeds.html'>SEEDS</a></b></li>";
    content += "<li><b><a href='system.html'>SYSTEM</a></b></li>";
    content += "<li><b><a class='active' href='statistics.html'>STATISTICS</a></b></li>";
    content += "<li><b><a href='https://digibyte.help' target='_blank'>Help</a></b></li>";
    content += "</ul>";
    content += "<div style='margin-left:25%;padding:1px 16px;height:1000px;'>";
    if(!fTestNet){ content += "<h1><b>" + e_ns + "</b></h1>\n\n"; }else{ content += "<h1><b>" + e_ns + " - ( Testnet )</b></h1>\n\n"; }
    content += "<p><b>Available:</b> " + xa +" / " + xb + "</p>\n";
    content += "<p><b>Attempts:</b> " + xc + " <b>/</b> " + xd + " Seconds</p>\n";
    content += "<p><b>New:</b> " + xe + "</p>\n<p><b>Active:</b> " + xf + "</p>\n<p><b>Banned:</b> " + xg + "</p>\n";
    content += "<p><b>DNS requests:</b> " + xi + "</p>\n<p><b>DB queries:</b> " + xj + "</p>\n";
    content += "</div>\n";
    content += "</body>\n</html>\n";
    response.SetHeader("Content-Type", "text/html");
    response.SetContent(content);
    return response;
};
  //statistics
