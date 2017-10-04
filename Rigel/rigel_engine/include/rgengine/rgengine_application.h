
namespace rg::rgengine{

	class RgEngineApplication {
	public:
		RgEngineApplication();
		~RgEngineApplication();

		void Run();
	private:
		RgEngineApplication(const RgEngineApplication&) = delete;
		RgEngineApplication& operator=(const RgEngineApplication&) = delete;
	};
}