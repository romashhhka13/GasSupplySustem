#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "GasSupplySystem.h"
#include "Graph.h"
#include "Addition.h"
#include "Pipe.h"
#include "Station.h"

void MenuShowObjects(GasSupplySystem& gss);
void MenuSave(GasSupplySystem& gss);
void MenuLoad(GasSupplySystem& gss);
void MenuEditPipes(GasSupplySystem& gss);
void MenuEditCS(GasSupplySystem& gss);
void MenuDelete(GasSupplySystem& gss);
void MenuNetwork(GasSupplySystem& gss);