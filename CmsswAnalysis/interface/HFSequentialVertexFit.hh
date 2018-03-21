#ifndef GUARD_HFSEQUENTIALVERTEXFIT_H
#define GUARD_HFSEQUENTIALVERTEXFIT_H

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"

#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicTree.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "Bmm/CmsswAnalysis/interface/HFDecayTree.hh"

#include <vector>



class HFSequentialVertexFit {
public:
  HFSequentialVertexFit(edm::Handle<edm::View<reco::Track> > hTracks,
			const reco::MuonCollection* muons,
			const TransientTrackBuilder *TTB,
			edm::Handle<reco::VertexCollection> pvCollection,
			const MagneticField *field,
			reco::BeamSpot beamSpot,
			int verbose = 0, bool removeCandTracksFromVtx = true);

  virtual ~HFSequentialVertexFit();

  void doFit(HFDecayTree *tree);
  void setPvW8(double x) {fPvW8 = x;}
  void useBeamspotConstraint(bool val) {fUseBeamspotConstraint = val;}

private:
  bool fitTree(HFDecayTree *tree);
  bool passAllCuts(HFDecayTree *tree);
  void calculateAll(HFDecayTree *tree);
  void calculateStuff(HFDecayTree *tree, VertexState *);
  void saveTree(HFDecayTree *tree);

  double getMaxDoca(std::vector<RefCountedKinematicParticle> &kinParticles);
  double getMinDoca(std::vector<RefCountedKinematicParticle> &kinParticles);

  // wrapper for the template routine bellow
  TAnaCand *addCandidate(HFDecayTree *tree, VertexState *wrtVertexState = NULL);
  float getParticleMass(int particleID, float *mass_sigma);
  void computeDaughterDistance(HFDecayTree *tree);
  void addFittedParticles(std::vector<RefCountedKinematicParticle> *kinParticles, HFDecayTree *decayTree);


  // to create a covariance matrix for error propagation
  cov99_t makeCovarianceMatrix(cov33_t cov_vtx1, cov77_t cov_vtx2);
  cov33_t GlobalError2SMatrix_33(GlobalError);

  jac9_t makeJacobianVector3d(const AlgebraicVector3 &vtx1, const AlgebraicVector3 &vtx2, const AlgebraicVector3 &momentum);
  jac9_t makeJacobianVector3d(const ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>, ROOT::Math::DefaultCoordinateSystemTag> &vtx1,
			      const GlobalPoint &vtx2, const TVector3 &tv3momentum);
  jac9_t makeJacobianVector3d(const GlobalPoint &vtx1, const GlobalPoint &vtx2, const TVector3 &tv3momentum);

  jac9_t makeJacobianVector2d(const AlgebraicVector3 &vtx1, const AlgebraicVector3 &vtx2, const AlgebraicVector3 &momentum);
  jac9_t makeJacobianVector2d(const ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>, ROOT::Math::DefaultCoordinateSystemTag> &vtx1,
			      const GlobalPoint &vtx2, const TVector3 &tv3momentum);
  jac9_t makeJacobianVector2d(const GlobalPoint &vtx1, const GlobalPoint &vtx2, const TVector3 &tv3momentum);

private:
  int                                  fVerbose;
  const TransientTrackBuilder         *fpTTB;
  edm::Handle<edm::View<reco::Track> > fhTracks;
  edm::Handle<reco::VertexCollection>  fPVCollection;
  const reco::MuonCollection          *fMuons;
  const MagneticField                 *fMagneticField;
  reco::BeamSpot                       fBeamSpot;
  bool                                 fRemoveCandTracksFromVtx;

  double                               fPvW8;
  bool                                 fUseBeamspotConstraint;
};

#endif
