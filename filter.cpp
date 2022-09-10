#include "pch.h"
#include "real-xxxgan-filter.h"

static RealXxxGanFilter* plugin = nullptr;

static constexpr int NumTrackbarItems = 3;
static TCHAR* TrackbarNames[NumTrackbarItems] = { "スケール", "デノイズ", "TTA" };
static int TrackbarDefaults[NumTrackbarItems] = { 2, -1, 0 };
static int TrackbarMins[NumTrackbarItems] = { 1, -1, 0 };
static int TrackbarMaxs[NumTrackbarItems] = { 4, 3, 1 };

static constexpr int NumRadioButtonItems = 4;
static TCHAR* RadioButtonNames[NumRadioButtonItems] = { "Real-CUGAN", "Real-ESRGAN AnimeVideo-v3", "Real-ESRGAN x4plus", "Real-ESRGAN x4plus-anime" };
static int RadioButtonDefaults[NumRadioButtonItems] = { 1, 0, 0, 0 };

BOOL InitPlugin(FILTER* fp) {
	if (plugin) {
		delete plugin;
	}

	plugin = new RealXxxGanFilter();

	return TRUE;
}

BOOL ExitPlugin(FILTER* fp) {
	if (plugin) {
		delete plugin;
		plugin = nullptr;
	}

	return TRUE;
}

BOOL ProcPlugin(FILTER* fp, FILTER_PROC_INFO* fpip) {
	if (!plugin) {
		MessageBoxW(NULL, L"Plugin not initialized!\n", L"Real-xxxGAN", MB_OK);
		return FALSE;
	}

	Mode mode = Mode::RealCUGAN;
	if (fp->check[0]) {
		mode = Mode::RealCUGAN;
	}
	else if (fp->check[1]) {
		mode = Mode::RealESRGAN_AnimeVideoV3;
	}
	else if (fp->check[2]) {
		mode = Mode::RealESRGAN_X4Plus;
	}
	else if (fp->check[3]) {
		mode = Mode::RealESRGAN_X4PlusAnime;
	}

	int scale = fp->track[0];
	if (mode == Mode::RealESRGAN_X4Plus || mode == Mode::RealESRGAN_X4PlusAnime) {
		scale = 4;
	}

	int denoise = fp->track[1];
	if (mode == Mode::RealCUGAN) {
		if (scale >= 3 && denoise >= 1) {
			denoise = 3;
		}
	}
	else {
		denoise = 0;
	}

	bool tta = fp->track[2];

	int w = fpip->w;
	int h = fpip->h;
	int w_max = fpip->max_w;
	int h_max = fpip->max_h;
	int w_out = std::min(w_max, scale * w);
	int h_out = std::min(h_max, scale * h);

	if (!plugin->SetSize(w, h, scale)) {
		MessageBoxW(NULL, L"Failed buffer allocation!\n", L"Real-xxxGAN", MB_OK);
		return FALSE;
	}

	for (int y = 0; y < h; ++y) {
		auto yc = &fpip->ycp_edit[w_max * y];
		auto bgra = &plugin->GetInputBuffer()[4 * w * y];

		for (int x = 0; x < w; ++x) {
			fp->exfunc->yc2rgb((PIXEL*)bgra, yc, 1);
			bgra[3] = 0xff;

			yc += 1;
			bgra += 4;
		}
	}

	if (!plugin->Process(mode, scale, denoise, tta)) {
		return FALSE;
	}

	for (int y = 0; y < h_out; ++y) {
		auto yc = &fpip->ycp_edit[w_max * y];
		auto bgra = &plugin->GetOutputBuffer()[4 * scale * w * y];

		for (int x = 0; x < w_out; ++x) {
			fp->exfunc->rgb2yc(yc, (PIXEL*)bgra, 1);

			yc += 1;
			bgra += 4;
		}
	}

	fpip->w = w_out;
	fpip->h = h_out;

	return TRUE;
}

EXTERN_C __declspec(dllexport) FILTER_DLL* __stdcall GetFilterTable(void)
{
	static FILTER_DLL dll{};

	dll.flag = FILTER_FLAG_EX_INFORMATION | FILTER_FLAG_RADIO_BUTTON;
	dll.name = "Real-xxxGAN-filter";
	dll.track_n = NumTrackbarItems;
	dll.track_name = TrackbarNames;
	dll.track_default = TrackbarDefaults;
	dll.track_s = TrackbarMins;
	dll.track_e = TrackbarMaxs;
	dll.check_n = NumRadioButtonItems;
	dll.check_name = RadioButtonNames;
	dll.check_default = RadioButtonDefaults;
	dll.func_proc = ProcPlugin;
	dll.func_init = InitPlugin;
	dll.func_exit = ExitPlugin;

	return &dll;
}
