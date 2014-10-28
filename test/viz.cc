#include <gmi_mesh.h>
#include <apf.h>
#include <apfMesh.h>
#include <apfMesh2.h>
#include <apfMDS.h>
#include <PCU.h>
#include "../viz/viz.h"

namespace {
  const char* modelFile = 0;
  const char* meshFile = 0;
  
  void freeMesh(apf::Mesh* m)
  {
    m->destroyNative();
    apf::destroyMesh(m);
  }

  void getConfig(int argc, char** argv)
  {
    assert(argc==3);
    modelFile = argv[1];
    meshFile = argv[2];
  }
}
int main(int argc, char** argv)
{
  int provided;
  MPI_Init_thread(&argc,&argv,MPI_THREAD_MULTIPLE,&provided);
  assert(provided==MPI_THREAD_MULTIPLE);
  PCU_Comm_Init();
  gmi_register_mesh();
  getConfig(argc,argv);
  apf::Mesh2* m = apf::loadMdsMesh(modelFile,meshFile);
  
  apf::MeshIterator* itr = m->begin(0);
  apf::MeshEntity* ent;

  Visualization v;
  v.new_viz();
  std::cout<<"watching now"<<std::endl;
  while ((ent = m->iterate(itr))!=0) {
    v.watchEntity(m,ent);
    std::cout<<"watched entity"<<std::endl;
  }
  std::cout<<"breaking now"<<std::endl;
  v.breakpoint();
  v.end_viz();

  freeMesh(m);
  PCU_Comm_Free();
  MPI_Finalize();
}