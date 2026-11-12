/**
* --------------------------------------------------------------------------------------------------------------------
* <copyright company="Aspose" file="TestHtmlConversionApi.cpp">
*  Copyright (c) 2022 Aspose.HTML for Cloud
* </copyright>
* <summary>
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
* </summary>
* --------------------------------------------------------------------------------------------------------------------
*/
#include "TestBase.h"

using namespace com::aspose::api;

class TestHtmlConversionApi : public TestBase
{

public:
    std::shared_ptr<ConversionApi> api;
    std::shared_ptr<StorageApi> storage_api;

    boost::optional<utility::string_t> folder;
    boost::optional<utility::string_t> storage;
    utility::string_t name;
    boost::optional<utility::string_t> versionId;

    utility::string_t sourceUrl;
    double width;
    double height;
    double leftMargin;
    double rightMargin;
    double topMargin;
    double bottomMargin;

protected:

    void SetUp()
	{
        try 
        {
            std::shared_ptr<ApiConfiguration> apiConfig(new ApiConfiguration(clientId, clientSecret, basePath, authPath));
            std::shared_ptr<ApiClient> apiClient(new ApiClient(apiConfig));
            api = std::make_shared<ConversionApi>(apiClient);
            storage_api = std::make_shared<StorageApi>(apiClient);

            sourceUrl = _XPLATSTR("https://stallman.org/articles/anonymous-payments-thru-phones.html");
            folder = _XPLATSTR("HtmlTestDoc");
            storage = boost::none;
            name = _XPLATSTR("test1.html");

            width = 800;
            height = 1000;
            leftMargin = 50;
            rightMargin = 50;
            topMargin = 100;
            bottomMargin = 100;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }

    void TearDown()
    {
    }
};

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testLocalToLocalDocuments)
{

    utility::string_t formats[] = { L"pdf", L"xps", L"docx", L"mhtml", L"mht", L"md"};
    utility::string_t src = testSource + name;

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = testResult + L"testLocToLocDoc." + formats[i];

        auto result = api->convertLocalToLocal(src, dst);
        auto re = result->getFile();

        std::ifstream f(re.c_str());
        ASSERT_TRUE(f.good());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testLocalToLocalDocumentsWithOpts)
{

    utility::string_t formats[] = { L"pdf", L"xps", L"docx" };
    utility::string_t src = testSource + name;

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = testResult + L"testLocToLocDocWithOpts." + formats[i];

        std::shared_ptr<ConversionOptions> opts_A4 = std::make_shared<ConversionOptions>();
        opts_A4->setWidth(8.3)
            ->setHeight(11.7)
            ->setLeftMargin(0.2)
            ->setRightMargin(0.2)
            ->setTopMargin(0.2)
            ->setBottomMargin(0.2);

        auto result = api->convertLocalToLocal(src, dst, opts_A4);
        auto re = result->getFile();

        std::ifstream f(re.c_str());
        ASSERT_TRUE(f.good());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testLocalToLocalImages)
{

    utility::string_t formats[] = { L"jpeg", L"jpg", L"bmp", L"png", L"tiff", L"tif", L"gif" };
    utility::string_t src = testSource + name;

    std::shared_ptr<ConversionOptions> opts = std::make_shared<ConversionOptions>();
    opts->setWidth(width)
        ->setHeight(height)
        ->setLeftMargin(leftMargin)
        ->setRightMargin(rightMargin)
        ->setTopMargin(topMargin)
        ->setBottomMargin(bottomMargin);

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = testResult + L"testLocToLocImg." + formats[i];

        auto result = api->convertLocalToLocal(src, dst, opts);
        auto re = result->getFile();

        std::ifstream f(re.c_str());
        ASSERT_TRUE(f.good());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testLocalToStorageDocuments)
{

    utility::string_t formats[] = { L"pdf", L"xps", L"docx", L"mhtml", L"mht", L"md" };
    utility::string_t src = testSource + name;

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = L"HtmlDocCPP/testLocToStorDoc." + formats[i];
        boost::optional<utility::string_t> versionId = _XPLATSTR("");
        utility::string_t storage = _XPLATSTR("");

        auto result = api->convertLocalToStorage(src, dst, storage);
        auto filePath = result->getFile();

        auto result_exist = storage_api->objectExists(filePath, versionId, storage).get();

        ASSERT_TRUE(result_exist->isExists());
        ASSERT_FALSE(result_exist->isFolder());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testLocalToStorageImages)
{

    utility::string_t formats[] = { L"jpeg", L"jpg", L"bmp", L"png", L"tiff", L"tif", L"gif" };
    utility::string_t src = testSource + name;
    std::shared_ptr<ConversionOptions> opts = std::make_shared<ConversionOptions>();
    opts->setWidth(width)
        ->setHeight(height)
        ->setLeftMargin(leftMargin)
        ->setRightMargin(rightMargin)
        ->setTopMargin(topMargin)
        ->setBottomMargin(bottomMargin);

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = L"HtmlDocCPP/LocToStorImg." + formats[i];
        boost::optional<utility::string_t> versionId = _XPLATSTR("");
        utility::string_t storage = _XPLATSTR("");

        auto result = api->convertLocalToStorage(src, dst, storage, opts);
        auto filePath = result->getFile();

        auto result_exist = storage_api->objectExists(filePath, versionId, storage).get();

        ASSERT_TRUE(result_exist->isExists());
        ASSERT_FALSE(result_exist->isFolder());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testStorageToStorageDocuments)
{

    utility::string_t formats[] = { L"pdf", L"xps", L"docx", L"mhtml", L"mht", L"md" };
    utility::string_t src = name;

    std::shared_ptr<HttpContent> file(new HttpContent(testSource, name));
    utility::string_t folder = _XPLATSTR("/");

    auto res = storage_api->uploadFile(folder, file, storage).get();

    ASSERT_FALSE(res->errorsIsSet());

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = L"HtmlDoc/testLocToStorDoc." + formats[i];
        boost::optional<utility::string_t> versionId = _XPLATSTR("");
        utility::string_t storage = _XPLATSTR("");

        auto result = api->convertStorageToStorage(src, dst, storage);
        auto filePath = result->getFile();

        auto result_exist = storage_api->objectExists(filePath, versionId, storage).get();

        ASSERT_TRUE(result_exist->isExists());
        ASSERT_FALSE(result_exist->isFolder());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testStorageToStorageImages)
{

    utility::string_t formats[] = { L"jpeg", L"jpg", L"bmp", L"png", L"tiff", L"tif", L"gif" };
    utility::string_t src = name;


    std::shared_ptr<HttpContent> file(new HttpContent(testSource, name));
    utility::string_t folder = _XPLATSTR("/");

    auto res = storage_api->uploadFile(folder, file, storage).get();

    std::shared_ptr<ConversionOptions> opts = std::make_shared<ConversionOptions>();
    opts->setWidth(width)
        ->setHeight(height)
        ->setLeftMargin(leftMargin)
        ->setRightMargin(rightMargin)
        ->setTopMargin(topMargin)
        ->setBottomMargin(bottomMargin);

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = L"HtmlDocCPP/StorToStorImg." + formats[i];
        boost::optional<utility::string_t> versionId = _XPLATSTR("");
        utility::string_t storage = _XPLATSTR("");

        auto result = api->convertStorageToStorage(src, dst, storage, opts);
        auto filePath = result->getFile();

        auto result_exist = storage_api->objectExists(filePath, versionId, storage).get();

        ASSERT_TRUE(result_exist->isExists());
        ASSERT_FALSE(result_exist->isFolder());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testStorageToLocalDocuments)
{

    utility::string_t formats[] = { L"pdf", L"xps", L"docx", L"mhtml", L"mht", L"md" };
    utility::string_t src = name;

    std::shared_ptr<HttpContent> file(new HttpContent(testSource, name));
    utility::string_t folder = _XPLATSTR("/");

    auto res = storage_api->uploadFile(folder, file, storage).get();

    ASSERT_FALSE(res->errorsIsSet());

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = testResult + L"testStorToLocDoc." + formats[i];
        boost::optional<utility::string_t> versionId = _XPLATSTR("");
        utility::string_t storage = _XPLATSTR("");

        auto result = api->convertStorageToLocal(src, dst, storage);
        auto filePath = result->getFile();

        std::ifstream f(filePath.c_str());
        ASSERT_TRUE(f.good());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testStorageToLocalImages)
{

    utility::string_t formats[] = { L"jpeg", L"jpg", L"bmp", L"png", L"tiff", L"tif", L"gif" };
    utility::string_t src = name;


    std::shared_ptr<HttpContent> file(new HttpContent(testSource, name));
    utility::string_t folder = _XPLATSTR("/");

    auto res = storage_api->uploadFile(folder, file, storage).get();

    std::shared_ptr<ConversionOptions> opts = std::make_shared<ConversionOptions>();
    opts->setWidth(width)
        ->setHeight(height)
        ->setLeftMargin(leftMargin)
        ->setRightMargin(rightMargin)
        ->setTopMargin(topMargin)
        ->setBottomMargin(bottomMargin);

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = testResult + L"testStorToLocImg." + formats[i];
        boost::optional<utility::string_t> versionId = _XPLATSTR("");
        utility::string_t storage = _XPLATSTR("");

        auto result = api->convertStorageToLocal(src, dst, storage, opts);
        auto filePath = result->getFile();

        std::ifstream f(filePath.c_str());
        ASSERT_TRUE(f.good());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testUrlToLocalDocuments)
{

    utility::string_t formats[] = { L"pdf", L"xps", L"docx", L"mhtml", L"mht", L"md" };
    utility::string_t src =sourceUrl;

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = testResult + L"testUrlToLocDoc." + formats[i];

        auto result = api->convertUrlToLocal(src, dst);
        auto re = result->getFile();

        std::ifstream f(re.c_str());
        ASSERT_TRUE(f.good());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testUrlToLocalImages)
{

    utility::string_t formats[] = { L"jpeg", L"jpg", L"bmp", L"png", L"tiff", L"tif", L"gif" };
    utility::string_t src = sourceUrl;

    std::shared_ptr<ConversionOptions> opts = std::make_shared<ConversionOptions>();
    opts->setWidth(width)
        ->setHeight(height)
        ->setLeftMargin(leftMargin)
        ->setRightMargin(rightMargin)
        ->setTopMargin(topMargin)
        ->setBottomMargin(bottomMargin);

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = testResult + L"testUrlToLocImg." + formats[i];

        auto result = api->convertUrlToLocal(src, dst, opts);
        auto re = result->getFile();

        std::ifstream f(re.c_str());
        ASSERT_TRUE(f.good());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testUrlToStorageDocuments)
{

    utility::string_t formats[] = { L"pdf", L"xps", L"docx", L"mhtml", L"mht", L"md" };
    utility::string_t src = sourceUrl;

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = L"HtmlDocCPP/testUrlToStorDoc." + formats[i];
        boost::optional<utility::string_t> versionId = _XPLATSTR("");
        utility::string_t storage = _XPLATSTR("");

        auto result = api->convertUrlToStorage(src, dst, storage);
        auto filePath = result->getFile();

        auto result_exist = storage_api->objectExists(filePath, versionId, storage).get();

        ASSERT_TRUE(result_exist->isExists());
        ASSERT_FALSE(result_exist->isFolder());
    }
}

TEST_F(TestHtmlConversionApi, /*DISABLED_*/testUrlToStorageImages)
{

    utility::string_t formats[] = { L"jpeg", L"jpg", L"bmp", L"png", L"tiff", L"tif", L"gif" };
    utility::string_t src = sourceUrl;
    std::shared_ptr<ConversionOptions> opts = std::make_shared<ConversionOptions>();
    opts->setWidth(width)
        ->setHeight(height)
        ->setLeftMargin(leftMargin)
        ->setRightMargin(rightMargin)
        ->setTopMargin(topMargin)
        ->setBottomMargin(bottomMargin);

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = L"HtmlDocCPP/UrlToStorImg." + formats[i];
        boost::optional<utility::string_t> versionId = _XPLATSTR("");
        utility::string_t storage = _XPLATSTR("");

        auto result = api->convertUrlToStorage(src, dst, storage, opts);
        auto filePath = result->getFile();

        auto result_exist = storage_api->objectExists(filePath, versionId, storage).get();

        ASSERT_TRUE(result_exist->isExists());
        ASSERT_FALSE(result_exist->isFolder());
    }
}

// Cross-SDK scenario: the output path is passed as a user would (no leading '/').
// The result must land at exactly that storage path, not only at the path the
// API reports back.
TEST_F(TestHtmlConversionApi, /*DISABLED_*/testStorageToStorageLandsAtRequestedPath)
{
    utility::string_t inputFolder = _XPLATSTR("HtmlTestDoc");
    utility::string_t storage = _XPLATSTR("");
    boost::optional<utility::string_t> versionId = _XPLATSTR("");

    std::shared_ptr<HttpContent> file(new HttpContent(testSource, name));
    auto res = storage_api->uploadFile(inputFolder, file, storage).get();
    ASSERT_FALSE(res->errorsIsSet());
    ASSERT_FALSE(res->getUploaded().empty());
    utility::string_t src = res->getUploaded()[0];

    utility::string_t dst = _XPLATSTR("HtmlDocCPP/StorToStorRequestedPath.pdf");

    // Remove a result left over from a previous run so it cannot mask a miss.
    try
    {
        storage_api->deleteFile(dst, versionId, storage).get();
    }
    catch (...)
    {
    }

    auto result = api->convertStorageToStorage(src, dst, storage);

    ASSERT_EQ(result->getStatus(), utility::string_t(_XPLATSTR("completed")));
    std::wcout << L"Requested: " << dst << L", reported: " << result->getFile() << std::endl;

    auto result_exist = storage_api->objectExists(dst, versionId, storage).get();

    ASSERT_TRUE(result_exist->isExists()) << "Result not found at the requested storage path; API reported "
        << result->getFile();
    ASSERT_FALSE(result_exist->isFolder());
}

// Cross-SDK scenario: a multi-page image conversion returns a zip named after
// the requested output file (<output>.zip), e.g. testfile.png.zip.
TEST_F(TestHtmlConversionApi, /*DISABLED_*/testLocalToLocalMultiPageImagesReturnOutputNameZip)
{
    utility::string_t formats[] = { L"png", L"jpeg", L"bmp", L"gif" };
    utility::string_t src = testSource + _XPLATSTR("html_file_long.html");

    std::shared_ptr<ConversionOptions> opts = std::make_shared<ConversionOptions>();
    opts->setHeight(300)
        ->setWidth(1000)
        ->setLeftMargin(10)
        ->setRightMargin(10)
        ->setTopMargin(10)
        ->setBottomMargin(10);

    for (int i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i)
    {
        utility::string_t dst = testResult + L"testfile." + formats[i];
        utility::string_t expected = L"testfile." + formats[i] + L".zip";

        auto result = api->convertLocalToLocal(src, dst, opts);

        EXPECT_EQ(result->getStatus(), utility::string_t(_XPLATSTR("completed")));

        auto re = result->getFile();
        std::ifstream f(re.c_str(), std::ios::binary | std::ios::ate);
        EXPECT_TRUE(f.good()) << "Result file is missing";
        EXPECT_GT(static_cast<long long>(f.tellg()), 0) << "Result file is empty";

        utility::string_t lower = re;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::towlower);
        EXPECT_NE(lower.find(expected), utility::string_t::npos)
            << "Format " << formats[i]
            << ": expected result file name to contain " << expected
            << ", got " << re;
    }
}
