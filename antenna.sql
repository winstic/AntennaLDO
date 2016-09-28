CREATE TABLE algorithm(
    aId         INT         PRIMARY KEY NOT NULL, 
    aName       TEXT        NOT NULL,
    aEngName    TEXT        NOT NULL,
    aInfo       TEXT,
    aPyPath     TEXT
);

INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(1, "DCMODE_DE_1C", "DCMODE_DE_1C", "DCMODE_DE_1C algorithm", "./DEA4AD/trunk/algorithm/DCMODE_DE_1C/DCMODE_DE_1C_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(2, "DCMODE_DE_1C_Share", "DCMODE_DE_1C_Share", "DCMODE_DE_1C_Share algorithm", "./DEA4AD/trunk/algorithm/DCMODE_DE_1C_Share/DCMODE_DE_1C_Share_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(3, "DCMOEA_Econvex_1C", "DCMOEA_Econvex_1C", "DCMOEA_Econvex_1C algorithm", "./DEA4AD/trunk/algorithm/DCMOEA_Econvex_1C/DCMOEA_Econvex_1C_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(4, "DCMOEA_Econvex_1C_Share", "DCMOEA_Econvex_1C_Share", "DCMOEA_Econvex_1C_Share algorithm", "./DEA4AD/trunk/algorithm/DCMOEA_Econvex_1C_Share/DCMOEA_Econvex_1C_Share_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(5, "DCNSGA_II_DE", "DCNSGA_II_DE", "DCNSGA_II_DE algorithm", "./DEA4AD/trunk/algorithm/DCNSGA_II_DE/DCNSGA_II_DE_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(6, "DCPICMOA_DE", "DCPICMOA_DE", "DCPICMOA_DE algorithm", "./DEA4AD/trunk/algorithm/DCPICMOA_DE/DCPICMOA_DE_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(7, "differentialevolution_qs", "differentialevolution_qs", "differentialevolution_qs algorithm", "./DEA4AD/trunk/algorithm/differentialevolution_qs/differentialevolution_qs_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(8, "eADE", "eADE", "eADE algorithm", "./DEA4AD/trunk/algorithm/eADE/eADE_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(9, "Orthogonaldesign", "Orthogonaldesign", "Orthogonaldesign algorithm", "./DEA4AD/trunk/algorithm/Orthogonaldesign/orthogonaldesign_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(10, "PSO", "PSO", "PSO algorithm", "./DEA4AD/trunk/algorithm/PSO/pso_conf.py");
INSERT INTO algorithm(aId, aName, aEngName, aInfo, aPyPath) 
    VALUES(11, "Simple_GA", "Simple_GA", "Simple_GA algorithm", "./DEA4AD/trunk/algorithm/Simple_GA/Simple_GA_conf.py");

CREATE TABLE antennaProblem(
    pId         INT         PRIMARY KEY NOT NULL,
    pName       TEXT        NOT NULL,
    pEngName    TEXT        NOT NULL,
    pModelPath  TEXT,
    pInfo       TEXT,
    pPyPath     TEXT
);
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(1, "cone_spiral Antenna", "cone_spiral Antenna", "./images/Waveguide.png", "cone_spiral Antenna Problem", "./DEA4AD/trunk/problem/cone_spiral/cone_spiral_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(2, "feko_spiral_300_400 Antenna", "feko_spiral_300_400 Antenna", "./images/Waveguide.png", "feko_spiral_300_400 Antenna Problem", "./DEA4AD/trunk/problem/feko_spiral_300_400/feko_spiral_300_400_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(3, "helical Antenna", "helical Antenna", "./images/helical_antenna.png", "helical Antenna Problem", "./DEA4AD/trunk/problem/helical_antenna/helical_antenna_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(4, "Helix_Missile_feko Antenna", "Helix_Missile_feko Antenna", "./images/Helix_Missile_feko.png", "Helix_Missile_feko Antenna Problem", "./DEA4AD/trunk/problem/Helix_Missile_feko/Helix_Missile_feko_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(5, "hfss_four_dioples Antenna", "hfss_four_dioples Antenna", "./images/Waveguide.png", "hfss_four_dioples Antenna Problem", "./DEA4AD/trunk/problem/hfss_four_dioples/hfss_four_dioples_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(6, "hfss_printed Antenna", "hfss_printed Antenna", "./images/Waveguide.png", "hfss_printed Antenna Problem", "./DEA4AD/trunk/problem/hfss_printed/hfss_printed_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(7, "Log_spiral Antenna", "Log_spiral Antenna", "./images/Waveguide.png", "Log_spiral Antenna Problem", "./DEA4AD/trunk/problem/Log_spiral/Log_spiral_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(8, "patch Antenna", "patch Antenna", "./images/Waveguide.png", "patch Antenna Problem", "./DEA4AD/trunk/problem/patch/patch_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(9, "plane_spiral Antenna", "plane_spiral Antenna", "./images/Waveguide.png", "plane_spiral Antenna Problem", "./DEA4AD/trunk/problem/plane_spiral_antenna/plane_spiral_antenna_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(10, "Polygon_cone_spiral Antenna", "Polygon_cone_spiral Antenna", "./images/Polygon_cone_spiral.png", "Polygon_cone_spiral Antenna Problem", "./DEA4AD/trunk/problem/Polygon_cone_spiral/Polygon_cone_spiral_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(11, "reducedrank Antenna", "reducedrank Antenna", "./images/Waveguide.png", "reducedrank Antenna Problem", "./DEA4AD/trunk/problem/reducedrank/reducedrank_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(12,"robust Antenna", "robust Antenna", "./images/Waveguide.png", "robust Antenna Problem", "./DEA4AD/trunk/problem/robust/robust_problem_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(13, "robustC Antenna", "robustC Antenna", "./images/Waveguide.png", "robustC Antenna Problem", "./DEA4AD/trunk/problem/robustC/robustC_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(14, "sidelobes Antenna", "sidelobes Antenna", "./images/Waveguide.png", "sidelobes Antenna Problem", "./DEA4AD/trunk/problem/sidelobes/sidelobes_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(15, "sidelobes_2 Antenna", "sidelobes_2 Antenna", "./images/Waveguide.png", "sidelobes_2 Antenna Problem", "./DEA4AD/trunk/problem/sidelobes_2/sidelobes_2_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(16, "sidelobes_3 Antenna", "sidelobes_3 Antenna", "./images/Waveguide.png", "sidelobes_3 Antenna Problem", "./DEA4AD/trunk/problem/sidelobes_3/sidelobes_3_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(17, "SingleTwistedWires Antenna", "SingleTwistedWires Antenna", "./images/SingleTwistedWires_feko.png", "SingleTwistedWires Antenna Problem", "./DEA4AD/trunk/problem/SingleTwistedWires/SingleTwistedWires_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(18, "SingleTwistedWires_feko Antenna", "SingleTwistedWires_feko Antenna", "./images/SingleTwistedWires_feko.png", "SingleTwistedWires_feko Antenna Problem", "./DEA4AD/trunk/problem/SingleTwistedWires_feko/SingleTwistedWires_feko_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(19, "spherical_spiral Antenna", "spherical_spiral Antenna", "./images/Waveguide.png", "spherical_spiral Antenna Problem", "./DEA4AD/trunk/problem/spherical_spiral/spherical_spiral_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(20, "spiral_antenna_nec Antenna", "spiral_antenna_nec Antenna", "./images/Waveguide.png", "spiral_antenna_nec Antenna Problem", "./DEA4AD/trunk/problem/spiral_antenna_nec/spiral_antenna_nec_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(21, "TDRS_C Antenna", "TDRS_C Antenna", "./images/Waveguide.png", "TDRS_C Antenna Problem", "./DEA4AD/trunk/problem/TDRS_C/TDRS_C_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(22, "Template_Problem_feko Antenna", "Template_Problem_feko Antenna", "./images/Waveguide.png", "Template_Problem_feko Antenna Problem", "./DEA4AD/trunk/problem/Template_Problem_feko/Template_Problem_feko_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(23, "Wave_cone_spiral Antenna", "Wave_cone_spiral Antenna", "./images/Wave_cone_spiral.png", "Wave_cone_spiral Antenna Problem", "./DEA4AD/trunk/problem/Wave_cone_spiral/Wave_cone_spiral_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(24, "wifiAntenna Antenna", "wifiAntenna Antenna", "./images/wifiAntenna.png", "wifiAntenna Antenna Problem", "./DEA4AD/trunk/problem/wifiAntenna/wifiAntenna_conf.py");
INSERT INTO antennaProblem(pId, pName, pEngName, pModelPath, pInfo, pPyPath) 
    VALUES(25, "Wire_Missile_feko Antenna", "Wire_Missile_feko Antenna", "./images/Wire_Missile_feko.png", "Wire_Missile_feko Antenna Problem", "./DEA4AD/trunk/problem/Wire_Missile_feko/Wire_Missile_feko_conf.py");

CREATE TABLE algtopro(
    mId INT PRIMARY KEY NOT NULL,
    pId INT NOT NULL,
    aId INT NOT NULL
);
INSERT INTO algtopro(mId, pId, aId) VALUES(1, 1, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(2, 1, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(3, 1, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(4, 1, 8);
INSERT INTO algtopro(mId, pId, aId) VALUES(5, 2, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(6, 2, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(7, 2, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(8, 2, 8);
INSERT INTO algtopro(mId, pId, aId) VALUES(9, 3, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(10, 3, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(11, 3, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(12, 4, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(13, 4, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(14, 5, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(15, 6, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(16, 7, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(17, 8, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(18, 9, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(19, 10, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(20, 11, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(21, 12, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(22, 13, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(23, 14, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(24, 15, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(25, 16, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(26, 17, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(27, 18, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(28, 19, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(29, 20, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(30, 21, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(31, 22, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(32, 22, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(33, 22, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(34, 22, 8);
INSERT INTO algtopro(mId, pId, aId) VALUES(35, 23, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(36, 24, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(37, 24, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(38, 24, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(39, 24, 8);
INSERT INTO algtopro(mId, pId, aId) VALUES(40, 25, 5);
INSERT INTO algtopro(mId, pId, aId) VALUES(41, 25, 6);
INSERT INTO algtopro(mId, pId, aId) VALUES(42, 25, 7);
INSERT INTO algtopro(mId, pId, aId) VALUES(43, 25, 8);