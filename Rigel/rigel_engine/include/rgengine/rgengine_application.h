
namespace rg::rgengine{

	struct RgEngineExternalAdapter;

	class RgEngineApplication {
	public:
		RgEngineApplication();
		~RgEngineApplication();

		void Run(const RgEngineExternalAdapter& adapter);
	private:
		RgEngineApplication(const RgEngineApplication&) = delete;
		RgEngineApplication& operator=(const RgEngineApplication&) = delete;
	};
}