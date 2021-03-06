#define DEBUG_TYPE "myPass"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/BasicBlock.h"
#include "llvm/Instruction.h"
#include "llvm/User.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/ilist.h"

using namespace llvm;

STATISTIC(MyPassCounter, "Counts number of functions greeted");

namespace {
	struct MyPass : public FunctionPass {
		static char ID; // Pass identification, replacement for typeid
		MyPass() : FunctionPass(ID) {}
	
		virtual bool runOnFunction(Function &F) {
			++MyPassCounter;
			errs() << "MyPass: ";
			errs() << "Function " << F.getName() << '\n';
			this->getBlocks(F);
			return false;
		}
		void getBlocks(Function &F) {
			int i = 0;
			for (Function::iterator bb = F.begin(), e = F.end(); bb != e; ++bb) {
				i++;
				errs() << " Basic block "<< i <<"\n";
				getInstructions(*bb);
			}
		}
		void getInstructions(BasicBlock &B) {
			for (BasicBlock::iterator i = B.begin(), e = B.end(); i != e; ++i) {
				errs() << "  " << i->getOpcodeName();
				getOperands(*i);
			}
		}
		void getOperands(Instruction &I) {
			for (User::op_iterator op = I.op_begin(), e = I.op_end(); op != e; ++op) {
				errs() << " " << **op;
			}
			errs() << "\n";
		}
	};
}

char MyPass::ID = 0;
static RegisterPass<MyPass> X("myPass", "My pass: get instructions' names");
